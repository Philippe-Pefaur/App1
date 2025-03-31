#ifndef METRICS_H
#define METRICS_H

// Función que registra los diferentes nombres de las pizzas en las ordenes extraídas
// en una arreglo de strings externo a la función y, a su vez, guarda la cantidad de
// pizzas pedidas según su nomobre en un arreglo de enteros externo a la función.
// El proceso es tal que al finalizar, el número de pizzas pedidas de nombre nombres[i]
// se encuentra en sumas[i].
int conteo_por_nombre(char (*pnombres)[100], int (*psumas)[50], int *size, struct order *orders) {
    int i;
    int index = 0; // Variable de control que indica el primer espacio vació en el arreglo nombres y sumas.

    // Se itera por cada orden registrada.
    for (i = 0; i < *size; i++) {
        int j;
        int control = 0; // Variable de control que indica si se encontró una coincidencia (1) o no (0).
        for (j = 0; j <= index; j++) // Se itera por cada elemento de nombres que no esté vacío más el primer elemento vacío.
            if (strcmp(*(pnombres + j), orders[i].pizza_name) == 0) { // Se revisa si el nombre de la pizza ya se encuentra en nobres.
                (*psumas)[j] += orders[i].quantity; // Si se encuentra en la nombres se suma su cantidad a sumas en el mismo ídice que fue encontrada la coincidencia.
                control = 1; // Se modifica control indicando que sí se encontró una coincidencia.
                break;
            }
        if (!control) {
            strcpy(*(pnombres + index), orders[i].pizza_name); // Si no, este es un nuevo nombre, entonces se registra en el primer espacio vacío de nombres.
            (*psumas)[index] = orders[i].quantity; // Se registra el número de pizzas pedidas en el primer índice vacío de ordenes.
            index++; // Se suma uno al índice para que este nuevamente corresponda al primer espacio vacío.
        }   
    }

    return index; // Se devuelve el último íncide vacío para saber cuántos nombres y sumas fueron registrados.
}

// Función que encuentra la pizza más vendida entre todas las ordenes.
char* pms(int *size, struct order *orders) {
    char nombres[50][100] = {0}; // Variable donde registrar los nombres de las diferentes pizzas.
    int sumas[50] = {0}; // Variable donde registrar las sumas de las cantidades de pizzas pedidas según su nombre.

    int index = conteo_por_nombre(nombres, &sumas, size, orders); // Se procesan las ordenes para completar los arreglos y se guarda el índice del primer elemento vacío.

    int i;
    int max_index = 0; // Variable de control que indica el índice de la suma más grande encontrada (inicalmente 0).
    for (i = 1; i < index; i++) { // Se itera por cada elemnto no vacío en sumas.
        if (sumas[i] > sumas[max_index]) { // Se revisa si la suma es mayor a la mayor suma encontrada.
            max_index = i; // Si sí, se registra el índice de esta suma en el índice con la suma más grnade.
        }
    }

    char *mas_vendido = (char*)malloc(100 * sizeof(char)); // Se asigna un espacio de memoria dinámico para guardar el nombre de la pizza más vendida.
    if (mas_vendido != NULL) { // Revisar que la memoria fué asignada correctamente.
        strcpy(mas_vendido, nombres[max_index]); // Si sí, copiar el nombre con el mismo índice donde se encontró la mayor suma al espacio.
    } 
    else {
        printf("ERROR al alocar memoria."); // Si no, adevertir error y terminar la función.
        return NULL;
    }

    return mas_vendido; // Se devuelve la dirección en el espacio de memoria donde se encuentra el nombre.
}

char* pls(int *size, struct order *orders) {
    char nombres[50][100] = {0}; // Variable donde registrar los nombres de las diferentes pizzas.
    int sumas[50] = {0}; // Variable donde registrar las sumas de las cantidades de pizzas pedidas según su nombre.
    
    int index = conteo_por_nombre(nombres, &sumas, size, orders); // Se procesan las ordenes para completar los arreglos y se guarda el índice del primer elemento vacío.

    int i;
    int min_index = 0; // Variable de control que indica el índice de la menor suma encontrada (inicalmente 0).
    for (i = 1; i < index; i++) { // Se itera por cada elemnto no vacío en sumas.
        if (sumas[i] < sumas[min_index]) { // Se revisa si la suma es menor a la menor suma encontrada.
            min_index = i; // Si sí, se registra el índice de esta suma en el índice con la menor suma.
        }
    }

    char *menos_vendido = (char*)malloc(100 * sizeof(char)); // Se asigna un espacio de memoria dinámico para guardar el nombre de la pizza menos vendida.
    if (menos_vendido != NULL) { // Revisar que la memoria fué asignada correctamente.
        strcpy(menos_vendido, nombres[min_index]); // Si sí, copiar el nombre con el mismo índice donde se encontró la menor suma al espacio.
    } 
    else {
        printf("ERROR al alocar memoria."); // Si no, adevertir error y terminar la función.
        return NULL;
    }

    return menos_vendido; // Se devuelve la dirección en el espacio de memoria donde se encuentra el nombre.
}

#endif