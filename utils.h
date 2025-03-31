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
               ingredientes_y_nombre); // Los últimos dos atributos son guardados en una sola variable para manejarlos aparte.
        
        char ingredientes[200] = {0}; // String donde se copia la lista de ingredientes del archivo.
        char nombre[100] = {0}; // String donde se guarda el nombre de la pizza.
        int indice = 0; // Primer índice sin ocupar en ingredientes.
        
        int suma = 0; // Variable de control para saber donde cortar ingredientes_y_nombre.
        int i;

        for (i = 0; i < sizeof(ingredientes_y_nombre); i++) { // Iterar  por cada caracter en ingredientes_y_nombre.
            if (suma < 2) { // Condicion para separar ingredientes de nombre.
                if (ingredientes_y_nombre[i] != '"') { // Si el caracter no es una " copiarlo al primer índice desocupado.
                    ingredientes[indice] = ingredientes_y_nombre[i];
                    indice++; // Incrementar en uno el primer índice desocupado.
                }
                else {
                    suma++; // Si el caracter sí es una " se incrementa suma en 1, cuando suma alcanze 2 significa que se llegó al final de la lista de ingredientes.
                }
            }
            else { // Se llegó al final de la lista de ingredientes.
                break;
            }
        }
        int ultimo = i + 1; // Se registra el último índice revisado como el ídice del caracter que está dos espacios después de donde se encontró la ", saltandose así la , divisoria del .csv.
        for (i = 0; i<sizeof(ingredientes_y_nombre); i++) { // Iterar por cada caracter en ingredientes_y_nombre.
            if (ingredientes_y_nombre[ultimo + i] == 0) { // Si tras la coma se lee un caracter nulo terminar el ciclo.
                break;
            }
            nombre[i] = ingredientes_y_nombre[ultimo + i]; // Si el caracter no es nulo copiarlo a nombre.
        }

        // Asignar los valores de ingredientes y nombre a sus atributos correspondientes.
        strcpy(current_order->pizza_ingredients, ingredientes);
        strcpy(current_order->pizza_name, nombre);

        (*size)++;
    }

    fclose(file);
    return orders;
}

#endif