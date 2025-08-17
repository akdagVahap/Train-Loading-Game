#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\train.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\vagon.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\material.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function initializes a Train structure with the provided ID 
// and sets it to an empty state (no wagons).
void initialize_train(Train* train, const char* train_id) {
    strcpy(train->train_id, train_id);
    train->first_wagon = NULL;
    train->wagon_count = 0;
}

// This function provides a detailed status report of the train, 
// including each wagon's weight and the materials it carries.
void display_train_status(const Train* train) {
    printf("Train ID: %s\n", train->train_id);
    printf("Wagons: %d\n", train->wagon_count);

    Wagon* current = train->first_wagon;
    while (current != NULL) {
        

        printf("  Wagon %d: %.2f/%.2f kg\n",
               current->wagon_id, current->current_weight, current->max_weight);

        LoadedMaterial* material = current->loaded_materials;
        while (material != NULL) {
            printf("    Material: %s, Loaded: %d, Weight per unit: %.2f\n",
                   material->type->name, material->type->loaded, material->type->weight);
            material = material->next;
        }

        
           

        current = current->next;
    }
}

// This function ensures that all memory used by the wagons 
// and loaded materials is properly freed, preventing memory leaks.
// After execution, the train is left with no wagons or materials.
void empty_train(Train* train) {
    Wagon* currentWagon = train->first_wagon;

    // Iterate through all wagons
    while (currentWagon != NULL) {
        // Free all loaded materials in the currentWagon wagon
        LoadedMaterial* materialLoaded = currentWagon->loaded_materials;
        while (materialLoaded != NULL) {
            LoadedMaterial* to_free = materialLoaded;
            materialLoaded = materialLoaded->next;
            free(to_free);
        }

        // Move to the next wagon and free the currentWagon wagon
        Wagon* to_free = currentWagon;
        currentWagon = currentWagon->next;
        free(to_free);
    }

    // Reset train properties
    // to block dangling pointer
    train->first_wagon = NULL;
    train->wagon_count = 0;

    printf("The train has been emptied!\n");
}