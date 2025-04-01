#ifndef UTILS_H
#define UTILS_H

struct order* read_csv(const char *filename, int *size);

// Función que registra los diferentes nombres de las pizzas en las ordenes extraídas
// en una arreglo de strings externo a la función y, a su vez, guarda la cantidad de
// pizzas pedidas según su nombre en un arreglo de enteros externo a la función.
// El proceso es tal que al finalizar, el número de pizzas pedidas de nombre nombres[i]
// se encuentra en sumas[i].
int conteo_por_nombre(char (*pnombres)[100], int (*psumas)[50], int *size, struct order *orders);

#endif