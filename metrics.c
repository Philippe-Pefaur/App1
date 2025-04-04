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
    char fechas[100][20] = {0};    // Arreglo para almacenar las fechas únicas de las órdenes (máximo 100 fechas de hasta 19 caracteres + null terminator)
    float totales[100] = {0.0};    // Arreglo paralelo que almacena la recaudación total por cada fecha
    int index = 0;                 // Índice para llevar la cuenta de cuántas fechas únicas se han almacenado

    // Agrupar total por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0; // Bandera para verificar si la fecha ya fue encontrada
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;  // Si la fecha ya está registrada, sumar el total de esta orden a su recaudación
                encontrada = 1;
                break;
            }
        }
        // Si la fecha no fue encontrada, se agrega como nueva
        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date); // Copiar la nueva fecha
            totales[index] = orders[i].total_price;      // Registrar el total de esta orden
            index++;                                     // Aumentar el contador de fechas únicas
        }
    }

    // Encontrar la fecha con mayor recaudación
    int max_index = 0;
    for (int i = 1; i < index; i++) {          // Iterar por las fechas únicas
        if (totales[i] > totales[max_index]) { // Si la recaudación de la fecha actual es mayor que la máxima encontrada
            max_index = i;                     // Actualizar el índice con el mayor total encontrado
        }
    }

    // Reservar espacio y formatear string
    char *resultado = (char*)malloc(100 * sizeof(char)); 
    if (resultado != NULL) {        // Formatear la cadena con la fecha y la recaudación más alta
        snprintf(resultado, 100, "%s con $%.2f", fechas[max_index], totales[max_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado; // Devolver la cadena con la fecha y el monto más alto recaudado
}

// Función que encuentra la fecha con menor recaudación total en dinero
char *dls(int *size, struct order *orders) {
    char fechas[100][20] = {0};   // Arreglo para almacenar las fechas únicas de las órdenes (máximo 100 fechas)
    float totales[100] = {0.0};   // Arreglo paralelo que almacena la recaudación total por cada fecha
    int index = 0;                // Índice para llevar la cuenta de cuántas fechas únicas se han almacenado

    // Recorrer todas las órdenes y agrupar el total recaudado por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;
        for (int j = 0; j < index; j++) {                           // Verificar si la fecha de la orden ya existe en el arreglo 'fechas'
            if (strcmp(fechas[j], orders[i].order_date) == 0) {
                totales[j] += orders[i].total_price;                // Si ya existe, sumar el total de esta orden al total acumulado de esa fecha
                encontrada = 1;
                break;
            }
        }
        // Si la fecha no fue encontrada, agregarla como nueva
        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);           // Copiar la nueva fecha al arreglo
            totales[index] = orders[i].total_price;                // Registrar el total de esta orden en el arreglo 'totales'
            index++;                                               // Aumentar el índice de las fechas
        }
    }

    // Buscar la fecha con menor recaudación
    int min_index = 0;
    for (int i = 1; i < index; i++) {
        if (totales[i] < totales[min_index]) {  //Compara la actual con la menor recaudación encontrada
            min_index = i;                      // Actualizar índice de menor recaudación
        }
    }

    // Crear string con la fecha y monto
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {                   // Formatear la cadena con la fecha y el monto menor
        snprintf(resultado, 100, "%s con $%.2f", fechas[min_index], totales[min_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;   // Devolver la cadena con la fecha y el monto más bajo recaudado
}

// Función que encuentra la fecha con mayor cantidad de pizzas vendidas
char *dmsp(int *size, struct order *orders) {
    char fechas[100][20] = {0}; // Arreglo para almacenar las fechas únicas de las órdenes (máximo 100 fechas)
    int cantidades[100] = {0};  // Arreglo paralelo que almacena la cantidad total de pizzas vendidas por cada fecha
    int index = 0;              // Índice para llevar la cuenta de cuántas fechas únicas se han almacenado

    // Agrupar la cantidad de pizzas vendidas por fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;                                       // Bandera para verificar si la fecha ya fue registrada
        for (int j = 0; j < index; j++) {                         // Buscar si la fecha ya está registrada en el arreglo 'fechas'
            if (strcmp(fechas[j], orders[i].order_date) == 0) {   // Si ya existe, sumar la cantidad de pizzas vendidas de esta orden
                cantidades[j] += orders[i].quantity;
                encontrada = 1;
                break;
            }
        }
        // Si la fecha no está registrada, agregarla como nueva
        if (!encontrada) {
            strcpy(fechas[index], orders[i].order_date);          // Copiar la nueva fecha al arreglo
            cantidades[index] = orders[i].quantity;               // Registrar la cantidad de pizzas vendidas de esta orden
            index++;                                              // Aumentar el índice de las fechas únicas
        }
    }

    // Buscar la fecha con más pizzas vendidas
    int max_index = 0;
    for (int i = 1; i < index; i++) {                   // Iterar por las fechas únicas
        if (cantidades[i] > cantidades[max_index]) {    // Compara la cantidad actual con la mayor cantidad encontrada
            max_index = i;                              // Actualizar índice con el valor máximo encontrado
        }
    }

    // Crear string con la fecha y cantidad
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {                            // Formatear la cadena con la fecha y cantidad máxima
        snprintf(resultado, 100, "%s con %d pizzas", fechas[max_index], cantidades[max_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado; // Devolver la cadena con la fecha y la cantidad máxima de pizzas vendidas
}

// Función que encuentra la fecha con menor cantidad de pizzas vendidas
char *dlsp(int *size, struct order *orders) {
    char fechas[100][20] = {0};                       // Arreglo para almacenar las fechas únicas de las órdenes (máximo 100 fechas)
    int cantidades[100] = {0};                        // Arreglo paralelo que almacena la cantidad total de pizzas vendidas por cada fecha
    int index = 0;                                    // Índice para llevar la cuenta de cuántas fechas únicas se han almacenado

    // Agrupar la cantidad de pizzas vendidas por cada fecha
    for (int i = 0; i < *size; i++) {
        int encontrada = 0;                           // Bandera para saber si la fecha ya fue registrada
        for (int j = 0; j < index; j++) {
            if (strcmp(fechas[j], orders[i].order_date) == 0) { 
                cantidades[j] += orders[i].quantity;  // Si ya existe, sumar la cantidad de pizzas vendidas a esa fecha
                encontrada = 1;
                break;
            }
        }
        // Si la fecha no fue encontrada, agregarla como nueva
        if (!encontrada) {                                // Copiar la nueva fecha
            strcpy(fechas[index], orders[i].order_date);  // Guardar cantidad de la orden
            cantidades[index] = orders[i].quantity;       // Incrementar índice de fechas únicas
            index++;
        }
    }

    // Buscar la fecha con menos pizzas vendidas
    int min_index = 0;
    for (int i = 1; i < index; i++) {
        if (cantidades[i] < cantidades[min_index]) {     // Compara la cantidad actual con la menor cantidad encontrada
            min_index = i;                               // Actualizar índice del mínimo si se encuentra uno menor
        }
    }

    // Crear string con la fecha y cantidad
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {     // Formatear la cadena con la fecha y la cantidad mínima encontrada
        snprintf(resultado, 100, "%s con %d pizzas", fechas[min_index], cantidades[min_index]);
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;    // Devolver el string con la fecha y la menor cantidad de pizzas vendidas
}

//Función que calcula el promedio de pizzas por orden
char *apo(int *size, struct order *orders) {
    int total_pizzas = 0;                       // Variable para contar el total de pizzas vendidas
    int ordenes_unicas[1000] = {0};             // Arreglo para almacenar los IDs de las órdenes únicas (máximo 1000)
    int total_ordenes = 0;                      // Contador de órdenes únicas


    // Recorrer todas las órdenes
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity;     // Sumar la cantidad de pizzas vendidas en cada orden

        // Revisar si este order_id ya fue contado
        int ya_conteada = 0;
        for (int j = 0; j < total_ordenes; j++) {
            if (ordenes_unicas[j] == orders[i].order_id) {
                ya_conteada = 1;              // Ya fue contabilizada esta orden
                break;
            }
        }
        // Si no ha sido contada, agregar el ID a la lista de órdenes únicas
        if (!ya_conteada) {
            ordenes_unicas[total_ordenes] = orders[i].order_id; 
            total_ordenes++;
        }
    }
    // Calcular el promedio como total de pizzas dividido por total de órdenes únicas
    float promedio = (float)total_pizzas / total_ordenes;

    // Reservar memoria para la cadena de resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "Promedio de pizzas por orden: %.2f", promedio);   // Formatear el resultado con dos decimales
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;   // Devolver el promedio calculado
}

//Función que calcula el promedio de pizzas por día
char *apd(int *size, struct order *orders) {
    int total_pizzas = 0;                   // Variable para contar el total de pizzas vendidas
    char fechas_unicas[1000][20];           // Arreglo para almacenar las fechas únicas de las órdenes (máximo 1000 fechas)
    int total_dias = 0;                     // Contador de fechas únicas
    
    // Recorrer todas las órdenes
    for (int i = 0; i < *size; i++) {
        total_pizzas += orders[i].quantity; // Sumar la cantidad de pizzas de la orden actual

        // Revisar si esta fecha ya fue contada
        int ya_conteada = 0;
        for (int j = 0; j < total_dias; j++) {
            if (strcmp(fechas_unicas[j], orders[i].order_date) == 0) {
                ya_conteada = 1;           // Fecha ya registrada
                break;
            }
        }
        // Si no ha sido contada, agregar la fecha a la lista de fechas únicas
        if (!ya_conteada) {           
            strcpy(fechas_unicas[total_dias], orders[i].order_date);
            total_dias++;
        }
    }
    // Calcular el promedio de pizzas por día
    float promedio = (float)total_pizzas / total_dias;

    // Reservar memoria para el string de resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "Promedio de pizzas por dia: %.2f", promedio); // Formatear el string con el promedio (2 decimales)
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado;   // Devolver el promedio calculado
}

// Función que encuentra el ingrediente más vendido entre todas las ordenes.
char *ims(int *size, struct order *orders) {
    struct ingrediente_total {
        char nombre[50];        // Nombre del ingrediente
        int cantidad;           // Cantidad total vendida de este ingrediente
    } ingredientes[1000];       // Arreglo para almacenar los ingredientes y sus cantidades (máximo 1000 ingredientes)

    int ingredientes_count = 0; // Contador de ingredientes únicos
    
    // Recorrer todas las órdenes   
    for (int i = 0; i < *size; i++) {
        char ingredientes_linea[200];   // Copiar la cadena de ingredientes de la orden actual a una variable editable
        strcpy(ingredientes_linea, orders[i].pizza_ingredients); 

        // Separar los ingredientes por comas usando strtok
        char *token = strtok(ingredientes_linea, ",");
        while (token != NULL) {
            // Eliminar espacios iniciales si hay
            while (*token == ' ') token++;

            int encontrado = 0; // Bandera para verificar si el ingrediente ya fue encontrado
            // Buscar si este ingrediente ya fue contado antes
            for (int j = 0; j < ingredientes_count; j++) {
                if (strcmp(ingredientes[j].nombre, token) == 0) { // Si ya existe, sumar la cantidad de pizzas de esta orden
                    ingredientes[j].cantidad += orders[i].quantity;
                    encontrado = 1;
                    break;
                }
            }
            // Si no fue encontrado, agregarlo como nuevo ingrediente
            if (!encontrado) {
                strcpy(ingredientes[ingredientes_count].nombre, token);
                ingredientes[ingredientes_count].cantidad = orders[i].quantity; 
                ingredientes_count++; // Aumentar el contador de ingredientes únicos
            }

            token = strtok(NULL, ",");
        }
    }

    // Buscar el ingrediente con mayor cantidad vendida
    int max_index = 0;
    for (int i = 1; i < ingredientes_count; i++) {
        if (ingredientes[i].cantidad > ingredientes[max_index].cantidad) { // Compara la cantidad actual con la mayor cantidad encontrada
            max_index = i; // Actualizar el índice del ingrediente más vendido
        }
    }

    // Reservar memoria para el resultado
    char *resultado = (char*)malloc(100 * sizeof(char));
    if (resultado != NULL) {
        snprintf(resultado, 100, "%s con %d unidades", ingredientes[max_index].nombre, ingredientes[max_index].cantidad); // Formatear el string con el nombre del ingrediente y la cantidad vendida
    } else {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    return resultado; // Devolver el string con el resultado
}

// Función que encuentra la cantidad de pizzas por categoría
char *hp(int *size, struct order *orders) {
    // Estructura para asociar una categoría con su cantidad total de pizzas vendidas
    struct categoria_total {
        char categoria[20]; // Nombre de la categoría
        int cantidad;       // Cantidad total de pizzas vendidas en esta categoría
    } categorias[100];      // Arreglo para almacenar las categorías y sus cantidades (máximo 100 categorías)

    int cat_count = 0;      // Contador de categorías únicas

    // Recorrer todas las órdenes
    for (int i = 0; i < *size; i++) {
        int encontrada = 0; // Bandera para saber si la categoría ya fue registrada
        for (int j = 0; j < cat_count; j++) {
            if (strcmp(categorias[j].categoria, orders[i].pizza_category) == 0) { // Si ya existe, sumar la cantidad de pizzas de esta orden
                categorias[j].cantidad += orders[i].quantity; 
                encontrada = 1; 
                break;
            }
        }
        // Si no se encontró, agregar la nueva categoría
        if (!encontrada) {
            strcpy(categorias[cat_count].categoria, orders[i].pizza_category);
            categorias[cat_count].cantidad = orders[i].quantity;
            cat_count++;
        }
    }

    // Reservar memoria para el string de resultado
    char *resultado = (char *)malloc(500 * sizeof(char));
    if (resultado == NULL) {
        printf("ERROR al reservar memoria.\n");
        return NULL;
    }

    resultado[0] = '\0'; // Inicializar como string vacío

    // Construir una línea por cada categoría
    for (int i = 0; i < cat_count; i++) {
        char linea[100];
        snprintf(linea, 100, "%s: %d pizzas\n", categorias[i].categoria, categorias[i].cantidad); // Formatear la línea con la categoría y la cantidad
        strcat(resultado, linea); // Agregar línea al string final
    }

    return resultado; // Devolver el string con todas las categorías y sus cantidades
}