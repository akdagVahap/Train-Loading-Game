#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\file_ops.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\vagon.h"

// This function ensures that all train data, 
// including wagons and materials, is saved to a file so that it can be reloaded later.
void save_train_to_file(const Train* train, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("There is an Error: Couldn't open file for saving.\n");
        return;
    }

    fprintf(file, "Train ID: %s\n", train->train_id);
    fprintf(file, "Wagon Count: %d\n", train->wagon_count);

    Wagon* currentWagon = train->first_wagon;
    while (currentWagon != NULL) {
        fprintf(file, "Wagon %d %.2f %.2f\n", currentWagon->wagon_id,
                currentWagon->current_weight, currentWagon->max_weight);

        LoadedMaterial* materialLoaded = currentWagon->loaded_materials;
        while (materialLoaded) {
            fprintf(file, "Material %s %d\n",
                    materialLoaded->type->name, materialLoaded->type->loaded);
            materialLoaded = materialLoaded->next;
        }
        currentWagon = currentWagon->next;
    }
    fclose(file);
    printf("train saved to file %s.\n", filename);
}

// This function removes any trailing spaces or tabs from a string, 
// leaving the content intact without unnecessary whitespace at the end.
void trim_trailing_whitespace(char* str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t')) {
        str[--len] = '\0';
    }
}

// This function reads train and wagon data from a file, 
// initializes the train structure, and remakes the wagons based on the saved data.
void load_train_from_file(Train* train, const char* filename, MaterialType* materials, int material_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file for loading.\n");
        return;
    }

    empty_train(train);  // Clear existing train data

    for (int i = 0; i < material_count; i++) {
        materials[i].loaded = 0;  // Reset material loaded counts
    }

    char train_id[20];
    int wagon_count;

    if (fscanf(file, "Train ID: %s\n", train_id) != 1) {
        printf("Error: Invalid file format (Train ID missing).\n");
        fclose(file);
        return;
    }

    if (fscanf(file, "Wagon Count: %d\n", &wagon_count) != 1) {
        printf("Error: Invalid file format (Wagon Count missing).\n");
        fclose(file);
        return;
    }

    initialize_train(train, train_id);

    for (int i = 0; i < wagon_count; i++) {
        int wagon_id;
        float current_weight, max_weight;

        if (fscanf(file, "Wagon %d %f %f\n", &wagon_id, &current_weight, &max_weight) != 3) {
            printf("Error: Invalid file format (Wagon data missing).\n");
            fclose(file);
            return;
        }

        Wagon* wagon = create_wagon(wagon_id);
        wagon->max_weight = max_weight;
        wagon->current_weight = current_weight;
        add_wagon(train, wagon);

        // Load materials into the wagon
        while (1) {
            char material_name[50];
            int loaded;

            if (fscanf(file, "Material %49[^\n] %d\n", material_name, &loaded) != 2) {
                break;  // No more materials for this wagon
            }

            // Trim any trailing whitespace from the material name
            trim_trailing_whitespace(material_name);

            // Find the corresponding material from the global list
            for (int j = 0; j < material_count; j++) {
                if (strcmp(materials[j].name, material_name) == 0) {
                    materials[j].loaded += loaded;  // Update loaded count

                    // Create and link the material to the wagon
                    LoadedMaterial* new_material = (LoadedMaterial*)malloc(sizeof(LoadedMaterial));
                    new_material->type = &materials[j];
                    new_material->next = wagon->loaded_materials;
                    new_material->prev = NULL;

                    if (wagon->loaded_materials) {
                        wagon->loaded_materials->prev = new_material;
                    }
                    wagon->loaded_materials = new_material;

                    printf("Debug: Loaded %d units of %s into Wagon %d.\n", loaded, material_name, wagon_id);
                    break;
                }
            }
        }
    }

    fclose(file);
    printf("Train loaded from %s.\n", filename);
}