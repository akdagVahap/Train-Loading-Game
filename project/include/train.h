#ifndef TRAIN_H
#define TRAIN_H
struct Wagon;
typedef struct Train {
    char train_id[20];    // Unique train identifier
    struct Wagon* first_wagon;   // Pointer to the first wagon
    int wagon_count;      // Total number of wagons
} Train;

// Initialize functions
void initialize_train(Train* train, const char* train_id);
void display_train_status(const Train* train);
void empty_train(Train* train);
#endif