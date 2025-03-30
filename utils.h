#ifndef UTILS_H
#define UTILS_H

# include "data_structures.h"
# include <string.h>

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

        char ingredientes_y_nombre[300]; 
        //Leer la lionea y aignar cada campo a la estructura
        struct order *current_order = &orders[*size];
        sscanf(line, "%d,%d,%49[^,],%d,%19[^,],%9[^,],%f,%f,%4[^,],%19[^,],%299[^\n]",
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
               ingredientes_y_nombre);
        
        char inicial = '"';
        int suma = 0;
        int i;
        char ingredientes[200] = {0};
        char nombre[100] = {0};
        int indice = 0;

        for (i = 0; i < sizeof(ingredientes_y_nombre); i++) {
            if (suma < 2) {
                if (ingredientes_y_nombre[i] != inicial) {
                    ingredientes[indice] = ingredientes_y_nombre[i];
                    indice++;
                }
                else {
                    suma++;
                }
            }
            else {
                break;
            }
        }
        int ultimo = i + 1;
        for (i = 0; i<sizeof(ingredientes_y_nombre); i++) {
            // char caracter = ingredientes_y_nombre[ultimo + i];
            if (ingredientes_y_nombre[ultimo + i] == 0) {
                break;
            }
            nombre[i] = ingredientes_y_nombre[ultimo + i];
        }

        strcpy(current_order->pizza_ingredients, ingredientes);
        strcpy(current_order->pizza_name, nombre);

        (*size)++;
    }

    fclose(file);
    return orders;
}

#endif