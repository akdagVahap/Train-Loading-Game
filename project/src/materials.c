#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\material.h"
#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\train.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\vagon.h"

// This function loads a specified quantity of a material into the train
void load_material(Train* train, MaterialType* material, int quantity) {
    int remaining = quantity;
    Wagon* currentWagon = train->first_wagon;

    while (remaining > 0) {
        if (currentWagon == NULL) {
            add_wagon(train, NULL); // Add a new empty wagon
            currentWagon = train->first_wagon;
            while (currentWagon->next != NULL) {
                currentWagon = currentWagon->next;
            }
        }

        // Check the top material in the current wagon
        if (currentWagon->loaded_materials != NULL) {
            float top_material_weight = currentWagon->loaded_materials->type->weight;

            if (material->weight > top_material_weight) {
                printf("Error: Cannot load %s into Wagon %d because it has lighter materials (%.2f kg per unit) on top.\n",
                       material->name, currentWagon->wagon_id, top_material_weight);
                break;
            }
        }

        float available_weight = currentWagon->max_weight - currentWagon->current_weight;
        int loadable = (int)(available_weight / material->weight);
        int to_load = (loadable < remaining) ? loadable : remaining;

        if (to_load > 0) {
            currentWagon->current_weight += to_load * material->weight;
            material->loaded += to_load;
            remaining -= to_load;

            // Add material to the wagon's loaded materials list
            LoadedMaterial* new_material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
            new_material->type = material;
            new_material->next = currentWagon->loaded_materials;
            new_material->prev = NULL;

            if (currentWagon->loaded_materials != NULL) {
                currentWagon->loaded_materials->prev = new_material;
            }
            currentWagon->loaded_materials = new_material;

            
        }

        if (remaining > 0) {
            currentWagon = currentWagon->next;
        }
    }

    if (remaining > 0) {
        printf("Warning: Could not load %d units of %s due to weight restrictions or lack of space.\n",
               remaining, material->name);
    }
}

void unload_material(Train* train, int wagon_id, int quantity) {
    Wagon* currentWagon = train->first_wagon;

    // girdiğim idyi bulana kadar vagon ara
    while (currentWagon != NULL && currentWagon->wagon_id != wagon_id) {
        currentWagon = currentWagon->next;
    }

    // vagon bulunmadıysa
    if (currentWagon == NULL) {
        printf("Wagon %d not found!\n", wagon_id);
        return;
    }

    int remaining = quantity;
    while (remaining > 0 && currentWagon != NULL) {
        LoadedMaterial* materialLoaded = currentWagon->loaded_materials;
        while (materialLoaded != NULL && remaining > 0) {

            // kaç tane çıkaracağın (ktç) yüklenen kutu sayısından küçükse, unloadable ktç ol, değilse yüklenen kutu sayısı ol
            // çıkarılabilecek kutu sayısı
            int unloadable = (remaining < materialLoaded->type->loaded) ? remaining : materialLoaded->type->loaded;

            // kaç tane çıkan * materyalin ağırlı = vagonun ağırlığı
            currentWagon->current_weight -= unloadable * materialLoaded->type->weight;
            
            // yüklenen kutu sayısını azaltıyor
            materialLoaded->type->loaded -= unloadable;

            // kaç tane çıkarıcağımızı azaltıyor
            remaining -= unloadable;

            // Remove the material node if fully unloaded

            // vagondaki kutu sayısı sıfırsa
            if (materialLoaded->type->loaded == 0) {

                // çıkarılacak materyal
                LoadedMaterial* to_free = materialLoaded;
                if (materialLoaded->prev) {
                    materialLoaded->prev->next = materialLoaded->next;
                }
                if (materialLoaded->next) {
                    materialLoaded->next->prev = materialLoaded->prev;
                }
                if (currentWagon->loaded_materials == materialLoaded) {
                    currentWagon->loaded_materials = materialLoaded->next;
                }
                materialLoaded = materialLoaded->next;
                free(to_free);
            } else {

                // şuanki materyali next materyale geçir
                materialLoaded = materialLoaded->next;
            }
        }

        // If the wagon is empty, remove it
        if (currentWagon->current_weight == 0) {
            Wagon* to_remove = currentWagon;

            if (currentWagon->prev) {
                currentWagon->prev->next = currentWagon->next;
            } else {
                train->first_wagon = currentWagon->next;
            }

            if (currentWagon->next) {
                currentWagon->next->prev = currentWagon->prev;
            }

            currentWagon = currentWagon->prev; // Move to the previous wagon
            free(to_remove);
            train->wagon_count--;
        } else {
            currentWagon = currentWagon->prev;
        }
    }

    if (remaining > 0) {
        printf("Not enough materials to unload %d units.\n", remaining);
    }
}

// This function loads a specified quantity of material into a specific wagon, 
// ensuring it doesn’t exceed the wagon’s weight capacity.
void load_material_to_specific_wagon(Train* train, MaterialType* material, int quantity, int wagon_id) {
    Wagon* currentWagon = train->first_wagon;

    // Find the specified wagon by ID
    while (currentWagon != NULL && currentWagon->wagon_id != wagon_id) {
        currentWagon = currentWagon->next;
    }

    if (currentWagon == NULL) {
        printf("Wagon %d not found!\n", wagon_id);
        return;
    }

    int remaining = quantity;
    float available_weight = currentWagon->max_weight - currentWagon->current_weight;
    int loadable = (int)(available_weight / material->weight);
    int to_load = (loadable < remaining) ? loadable : remaining;

    if (to_load > 0) {
        currentWagon->current_weight += to_load * material->weight;
        material->loaded += to_load;
        remaining -= to_load;

        // Add material to the wagon's loaded materials list
        LoadedMaterial* new_material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
        new_material->type = material;
        new_material->next = currentWagon->loaded_materials;
        new_material->prev = NULL;
        if (currentWagon->loaded_materials != NULL) {
            currentWagon->loaded_materials->prev = new_material;
        }
        currentWagon->loaded_materials = new_material;
    }

    if (remaining > 0) {
        printf("Not enough capacity in Wagon %d to load all materials. Remaining: %d\n", wagon_id, remaining);
    }
}

// This function unloads materials from the train, 
// starting with the first wagon, until the specified quantity is unloaded. 
// It automatically removes empty materials and wagons.
void unload_material_without_id(Train* train, int quantity) {
    int remaining = quantity;
    Wagon* currentWagon = train->first_wagon;

    while (remaining > 0 && currentWagon != NULL) {
        LoadedMaterial* materialLoaded = currentWagon->loaded_materials;
        while (materialLoaded != NULL && remaining > 0) {
            int unloadable = (remaining < materialLoaded->type->loaded) ? remaining : materialLoaded->type->loaded;
            currentWagon->current_weight -= unloadable * materialLoaded->type->weight;
            materialLoaded->type->loaded -= unloadable;
            remaining -= unloadable;

            // Remove the material node if fully unloaded
            if (materialLoaded->type->loaded == 0) {
                LoadedMaterial* to_free = materialLoaded;
                if (materialLoaded->prev) {
                    materialLoaded->prev->next = materialLoaded->next;
                }
                if (materialLoaded->next) {
                    materialLoaded->next->prev = materialLoaded->prev;
                }
                if (currentWagon->loaded_materials == materialLoaded) {
                    currentWagon->loaded_materials = materialLoaded->next;
                }
                materialLoaded = materialLoaded->next;
                free(to_free);
            } else {
                materialLoaded = materialLoaded->next;
            }
        }

        // If the wagon is empty, remove it
        if (currentWagon->current_weight == 0) {
            Wagon* to_remove = currentWagon;

            if (currentWagon->prev) {
                currentWagon->prev->next = currentWagon->next;
            } else {
                train->first_wagon = currentWagon->next;
            }

            if (currentWagon->next) {
                currentWagon->next->prev = currentWagon->prev;
            }

            Wagon* next_wagon = currentWagon->next;
            free(currentWagon);
            train->wagon_count--;
            currentWagon = next_wagon;
        } else {
            currentWagon = currentWagon->next;
        }
    }

    if (remaining > 0) {
        printf("Not enough materials to unload %d units.\n", remaining);
    }
}

// This function provides a detailed status report for all defined materials, 
// showing their properties and how many are currently loaded on the train.
void display_materials_status(MaterialType* materials, int count) {
    printf("\nMaterial Status:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n   Weight: %.2f, Total Available: %d, Loaded on Train: %d\n",
               i + 1, materials[i].name, materials[i].weight, materials[i].quantity, materials[i].loaded);
    }
}