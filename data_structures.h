#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

// Estructura para representar una orden
struct order {
    int pizza_id;                  // ID de la pizza
    int order_id;                  // ID de la orden
    char pizza_name_id[50];        // ID del nombre de la pizza
    int quantity;                  // Cantidad de pizzas
    char order_date[20];           // Fecha de la orden (formato: dd/mm/yyyy)
    char order_time[10];           // Hora de la orden (formato: hh:mm:ss)
    float unit_price;              // Precio unitario de la pizza
    float total_price;             // Precio total de la orden
    char pizza_size[5];            // Tamaño de la pizza (e.g., M, L)
    char pizza_category[20];       // Categoría de la pizza (e.g., Classic, Veggie)
    char pizza_ingredients[200];   // Ingredientes de la pizza
    char pizza_name[100];          // Nombre completo de la pizza
};

// Estructura que guarda el puntero, y el formato respectivo para su resultado, de cada función métrica
struct metricas {
    char* (*funcion)(int *size, struct order *orders); // Puntero función
    const char* formateo; // Formato para resultados
};


#endif