#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\file_ops.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\material.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\train.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\utils.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\vagon.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_BOX_TYPES 3

void display_box_types(MaterialType* materials, int count);

int main() {
    Train train;
    initialize_train(&train, "T123");

    // Define available box types
    MaterialType materials[MAX_BOX_TYPES] = {
        // name weight quantity loaded
        {"Large Box", 200.0, 50, 0},
        {"Medium Box", 100.0, 50, 0},
        {"Small Box", 50.0, 50, 0}
    };

    int userChoice;
    do {
        printf("\n Train Loading Management System \n");
        printf("1. Load Material\n");
        printf("2. Load Material to Specific Wagon\n");
        printf("3. Unload Material\n");
        printf("4. Unload Material Without Specifying Wagon\n");
        printf("5. Display Train Status\n");
        printf("6. Display Materials Status\n");
        printf("7. Empty Train\n");
        printf("8. Load Train from File\n");
        printf("9. Save Train to File\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1: {
                // Load material without specifying wagon
                int box_choice;
                int quantity;
                display_box_types(materials, MAX_BOX_TYPES);
                printf("What box do you want to load (1-%d): ", MAX_BOX_TYPES);
                scanf("%d", &box_choice);

                if (box_choice < 1 || box_choice > MAX_BOX_TYPES) {
                    printf("Invalid box type! Choose 1 or 2 or 3\n");
                } else {
                    printf("Enter quantity of %s to load: ", materials[box_choice - 1].name);
                    scanf("%d", &quantity);
                    load_material(&train, &materials[box_choice - 1], quantity);
                }
                break;
            }
            case 2: {
                // Load Material to Specific Wagon
                int wagon_id;
                int box_choice;
                int quantity;
                display_box_types(materials, MAX_BOX_TYPES);
                printf("Enter the box type to load (1-%d): ", MAX_BOX_TYPES);
                scanf("%d", &box_choice);

                if (box_choice < 1 || box_choice > MAX_BOX_TYPES) {
                    printf("Invalid box type! Choose 1 or 2 or 3\n");
                } else {
                    printf("Enter wagon ID to load into: ");
                    scanf("%d", &wagon_id);
                    printf("Enter quantity of %s to load: ", materials[box_choice - 1].name);
                    scanf("%d", &quantity);
                    load_material_to_specific_wagon(&train, &materials[box_choice - 1], quantity, wagon_id);
                }
                break;
            }
            case 3: {
                // Unload Material
                int wagon_id, quantity;
                printf("Enter wagon ID to unload from: ");
                scanf("%d", &wagon_id);
                printf("Enter quantity to unload: ");
                scanf("%d", &quantity);
                unload_material(&train, wagon_id, quantity);
                break;
            }
            case 4: {
                // Unload Material Without Specifying Wagon
                int quantity;
                printf("Enter quantity to unload from the end: ");
                scanf("%d", &quantity);
                unload_material_without_id(&train, quantity);
                break;
            }
            case 5:
                // Display Train Status
                display_train_status(&train);
                break;
            case 6:
                // Display Materials Status
                display_materials_status(materials, MAX_BOX_TYPES);
                break;
            case 7:
                // Empty The Train
                empty_train(&train);
                break;
            case 8: {
                // Load Train From File
                char filename[50];
                printf("Enter filename to load train data: ");
                scanf("%s", filename);
                load_train_from_file(&train, filename, materials, MAX_BOX_TYPES);
                break;
            }
            case 9: {
                // Save Train To File
                char filename[50];
                printf("Enter filename to save train data: ");
                scanf("%s", filename);
                save_train_to_file(&train, filename);
                break;
            }
            case 10:
                // Exit The Program
                printf("Exiting the program\n");
                break;
            default:
                // Wrong Choice
                printf("Invalid choice. Please try again Choose 1-10.\n");
        }
    } while (userChoice != 10);

    return 0;
}

// Helper Function to Display Box Types
void display_box_types(MaterialType* materials, int count) {
    printf("\nAvailable Box Types:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s (Weight: %.2f, Available: %d)\n",
               i + 1, materials[i].name, materials[i].weight, materials[i].quantity);
    }
}