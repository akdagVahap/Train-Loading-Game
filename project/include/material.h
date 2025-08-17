#ifndef MATERIAL_H
#define MATERIAL_H

struct Train;
struct MaterialType;

typedef struct LoadedMaterial {
    struct MaterialType* type;   // Type of box
    struct LoadedMaterial *next, *prev;
} LoadedMaterial;

typedef struct MaterialType {
    char name[50];
    float weight;
    int quantity;
    int loaded;
} MaterialType;

// Initialize functions
void initialize_material(MaterialType* material, const char* name, float weight, int quantity);
void load_material(struct Train* train, MaterialType* material, int quantity);
void unload_material(struct Train* train, int wagon_id, int quantity);
void load_material_to_specific_wagon(struct Train* train, MaterialType* material, int quantity, int wagon_id);
void unload_material_without_id(struct Train* train, int quantity);
void display_materials_status(MaterialType* materials, int count);

#endif // MATERIAL_H