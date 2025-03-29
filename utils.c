#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "data_structures.h"

// Función para leer el archivo CSV y cargar las órdenes
struct order* read_csv(const char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: No se pudo abrir el archivo %s\n", filename);
        return NULL;
    }

    // Arreglo dinámico para almacenar las órdenes
    struct order *orders = NULL;
    *size = 0;

    char line[1024];
    // Leer cada línea del archivo (ignorando la primera línea de encabezados)
    fgets(line, sizeof(line), file); // Leer encabezado y descartarlo
    while (fgets(line, sizeof(line), file)) {
        // Aumentar el tamaño del arreglo para la nueva orden
        orders = realloc(orders, (*size + 1) * sizeof(struct order));
        if (!orders) {
            printf("Error: No se pudo asignar memoria.\n");
            fclose(file);
            return NULL;
        }

        //Leer la lionea y aignar cada campo a la estructura
        struct order *current_order = &orders[*size];
        sscanf(line, "%d,%d,%49[^,],%d,%19[^,],%9[^,],%f,%f,%4[^,],%19[^,],%199[^,],%99[^\n]",
               &current_order->pizza_id,
               &current_order->order_id,
               current_order->pizza_name_id,
               &current_order->quantity,
               current_order->order_date,
               current_order->order_time,
               &current_order->unit_price,
               &current_order->total_price,
               current_order->pizza_size,
               current_order->pizza_category,
               current_order->pizza_ingredients,
               current_order->pizza_name);

        (*size)++;
    }

    fclose(file);
    return orders;
}