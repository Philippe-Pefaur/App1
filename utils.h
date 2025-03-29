#ifndef UTILS_H
#define UTILS_H

#include "data_structures.h"

// Declaración de la función para leer el archivo CSV
struct order* read_csv(const char *filename, int *size);

#endif