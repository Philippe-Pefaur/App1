#ifndef METRICS_H
#define METRICS_H

// Función que encuentra la pizza más vendida entre todas las ordenes.
char* pms(int *size, struct order *orders); 

// Función que encuentra la pizza menos vendida entre todas las ordenes.
char* pls(int *size, struct order *orders); 

// Función que encuentra la fecha con mayor recaudación total en dinero
char *dms(int *size, struct order *orders); 

// Función que encuentra la fecha con menor recaudación total en dinero
char *dls(int *size, struct order *orders); 

// Función que encuentra la fecha con mayor cantidad de pizzas vendidas
char *dmsp(int *size, struct order *orders); 

// Función que encuentra la fecha con menor cantidad de pizzas vendidas
char *dlsp(int *size, struct order *orders); 

//Función que calcula el promedio de pizzas por orden
char *apo(int *size, struct order *orders); 

//Función que calcula el promedio de pizzas por día
char *apd(int *size, struct order *orders); 

// Función que encuentra el ingrediente más vendido entre todas las ordenes.
char *ims(int *size, struct order *orders); 

// Función que encuentra la cantidad de pizzas por categoría
char *hp(int *size, struct order *orders); 

#endif