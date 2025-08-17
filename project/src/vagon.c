#include <stdio.h>
#include <stdlib.h>
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\train.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\vagon.h"

// This function creates and returns a new Wagon object
Wagon* create_wagon(int id) {
    Wagon* new_wagon = (Wagon*)malloc(sizeof(Wagon));
    new_wagon->wagon_id = id;
    new_wagon->max_weight = 1000.0;
    new_wagon->current_weight = 0.0;
    // null when starting
    new_wagon->loaded_materials = NULL;
    new_wagon->next = new_wagon->prev = NULL;
    return new_wagon;
}

// function to add wagon


// The add_wagon function is designed to add a new wagon to a Train. 
// It can either add an existing wagon (if provided) or create a new wagon if none is given.
void add_wagon(Train* train, Wagon* existing_wagon) {
    Wagon* new_wagon = existing_wagon;

    // Create a new wagon if none is provided
    if (new_wagon == NULL) {
        new_wagon = create_wagon(train->wagon_count + 1);
        
    } else {
        
    }

    // Add the wagon to the train
    if (train->first_wagon == NULL) {
        train->first_wagon = new_wagon;
    } else {
        Wagon* last = train->first_wagon;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = new_wagon;
        new_wagon->prev = last;
    }

    // Increment the wagon count
    train->wagon_count++;
    
}