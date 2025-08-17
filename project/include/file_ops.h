#ifndef FILEOPS_H
#define FILEOPS_H
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\train.h"
#include "C:\Users\akdag\OneDrive\Masaüstü\project\include\material.h"

// Initialize functions
void save_train_to_file(const Train* train, const char* filename);
void load_train_from_file(Train* train, const char* filename, MaterialType* materials, int material_count);

#endif