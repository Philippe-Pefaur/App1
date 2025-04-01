#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "utils.h"
#include "metrics.h"

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
        printf("ERROR al reservar memoria."); // Si no, adevertir error y terminar la función.
        return NULL;
    }

    return mas_vendido; // Se devuelve la dirección en el espacio de memoria donde se encuentra el nombre.
}

// Función que encuentra la pizza menos vendida entre todas las ordenes.
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
        printf("ERROR al reservar memoria."); // Si no, adevertir error y terminar la función.
        return NULL;
    }

    return menos_vendido; // Se devuelve la dirección en el espacio de memoria donde se encuentra el nombre.
}

// Función que encuentra la fecha con mayor recaudación total en dinero
char *dms(int *size, struct order *orders) {
    char fechas[100][20] = {0};
    float totales[100] = {0.0};
    int index = 0;

    // Agrupar total por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);
            totales[index] = orders[i].total_price;
            index++;
        }
    }

    // Encontrar la fecha con mayor recaudación
    int max_index = 0;
    for (int i = 1; i < index; i++) {
        if (totales[i] > totales[max_index]) {
            max_index = i;
        }
    }

    // Reservar espacio y formatear string
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con $%.2f", fechas[max_index], totales[max_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

// Función que encuentra la fecha con menor recaudación total en dinero
char *dls(int *size, struct order *orders) {
    char fechas[100][20] = {0};
    float totales[100] = {0.0};
    int index = 0;

    // Agrupar total recaudado por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);
            totales[index] = orders[i].total_price;
            index++;
        }
    }

    // Buscar la fecha con menor recaudación
    int min_index = 0;
    for (int i = 1; i < index; i++) {
        if (totales[i] < totales[min_index]) {
            min_index = i;
        }
    }

    // Crear string con la fecha y monto
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con $%.2f", fechas[min_index], totales[min_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

// Función que encuentra la fecha con mayor cantidad de pizzas vendidas
char *dmsp(int *size, struct order *orders) {
    char fechas[100][20] = {0};
    int cantidades[100] = {0};
    int index = 0;

    // Agrupar cantidades por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);
            cantidades[index] = orders[i].quantity;
            index++;
        }
    }

    // Buscar la fecha con más pizzas vendidas
    int max_index = 0;
    for (int i = 1; i < index; i++) {
        if (cantidades[i] > cantidades[max_index]) {
            max_index = i;
        }
    }

    // Crear string con la fecha y cantidad
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con %d pizzas", fechas[max_index], cantidades[max_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

// Función que encuentra la fecha con menor cantidad de pizzas vendidas
char *dlsp(int *size, struct order *orders) {
    char fechas[100][20] = {0};
    int cantidades[100] = {0};
    int index = 0;

    // Agrupar cantidad de pizzas por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);
            cantidades[index] = orders[i].quantity;
            index++;
        }
    }

    // Buscar la fecha con menos pizzas vendidas
    int min_index = 0;
    for (int i = 1; i < index; i++) {
        if (cantidades[i] < cantidades[min_index]) {
            min_index = i;
        }
    }

    // Crear string con la fecha y cantidad
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con %d pizzas", fechas[min_index], cantidades[min_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

//Función que calcula el promedio de pizzas por orden
char *apo(int *size, struct order *orders) {
    int total_pizzas = 0;
    int ordenes_unicas[1000] = {0};
    int total_ordenes = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        // Revisar si este order_id ya fue contado
        int ya_conteada = 0;
        for (int j = 0; j < total_ordenes; j++) {
            if (ordenes_unicas[j] == orders[i].order_id) {
                ya_conteada = 1;
                break;
            }
        }

        if (!ya_conteada) {
            ordenes_unicas[total_ordenes] = orders[i].order_id;
            total_ordenes++;
        }
    }

    float promedio = (float)total_pizzas / total_ordenes;

    // Crear string de resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "Promedio de pizzas por orden: %.2f", promedio);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

//Función que calcula el promedio de pizzas por día
char *apd(int *size, struct order *orders) {
    int total_pizzas = 0;
    char fechas_unicas[1000][20];
    int total_dias = 0;

    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;

        // Revisar si esta fecha ya fue contada
        int ya_conteada = 0;
        for (int j = 0; j < total_dias; j++) {
            if (strcmp(fechas_unicas[j], orders[i].order_date) == 0) {
                ya_conteada = 1;
                break;
            }
        }

        if (!ya_conteada) {
            strcpy(fechas_unicas[total_dias], orders[i].order_date);
            total_dias++;
        }
    }

    float promedio = (float)total_pizzas / total_dias;

    // Crear string de resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "Promedio de pizzas por dia: %.2f", promedio);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

// Función que encuentra el ingrediente más vendido entre todas las ordenes.
char *ims(int *size, struct order *orders) {
    struct ingrediente_total {
        char nombre[50];
        int cantidad;
    } ingredientes[1000];

    int ingredientes_count = 0;

    for (int i = 0; i < *size; i++) {
        char ingredientes_linea[200];
        strcpy(ingredientes_linea, orders[i].pizza_ingredients);

        char *token = strtok(ingredientes_linea, ",");
        while (token != NULL) {
            // Eliminar espacios iniciales si hay
            while (*token == ' ') token++;

            int encontrado = 0;
            for (int j = 0; j < ingredientes_count; j++) {
                if (strcmp(ingredientes[j].nombre, token) == 0) {
                    ingredientes[j].cantidad += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }

            if (!encontrado) {
                strcpy(ingredientes[ingredientes_count].nombre, token);
                ingredientes[ingredientes_count].cantidad = orders[i].quantity;
                ingredientes_count++;
            }

            token = strtok(NULL, ",");
        }
    }

    // Buscar el ingrediente más vendido
    int max_index = 0;
    for (int i = 1; i < ingredientes_count; i++) {
        if (ingredientes[i].cantidad > ingredientes[max_index].cantidad) {
            max_index = i;
        }
    }

    // Crear string de resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con %d unidades", ingredientes[max_index].nombre, ingredientes[max_index].cantidad);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;
}

// Función que encuentra la cantidad de pizzas por categoría
char *hp(int *size, struct order *orders) {
    struct categoria_total {
        char categoria[20];
        int cantidad;
    } categorias[100];

    int cat_count = 0;

    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(categorias[j].categoria, orders[i].pizza_category) == 0) {
                categorias[j].cantidad += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }

        if (!encontrada) {
            strcpy(categorias[cat_count].categoria, orders[i].pizza_category);
            categorias[cat_count].cantidad = orders[i].quantity;
            cat_count++;
        }
    }

    // Construir el string de resultado
    char *resultado = (char *)malloc(500 * sizeof(char));
    if (resultado == NULL) {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    resultado[0] = '\0'; // Inicializar como string vacío

    for (int i = 0; i < cat_count; i++) {
        char linea[100];
        snprintf(linea, 100, "%s: %d pizzas\n", categorias[i].categoria, categorias[i].cantidad);
        strcat(resultado, linea);
    }

    return resultado;
}