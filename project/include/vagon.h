#ifndef VAGON_H
#define VAGON_H
struct Train;
struct LoadedMaterial;
typedef struct Wagon {
    int wagon_id;         // Sequential ID
    float max_weight;     // Maximum weight capacity
    float current_weight; // Current weight loaded
    struct LoadedMaterial* loaded_materials; // List of loaded materials
    struct Wagon *next, *prev;
} Wagon;

// Initialize functions
Wagon* create_wagon(int id);
void add_wagon(struct Train* train, Wagon* new_wagon);
//void add_wagon(struct Train* train);
//void add_wagon(Train* train);
#endif