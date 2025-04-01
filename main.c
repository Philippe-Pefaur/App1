# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include "utils.h"
# include "data_structures.h"
# include "metrics.h"

int main(int argc, char *argv[]) {
    printf("Bienvenido al programa de análisis de ventas de la pizzería.\n");

    // Verificar que se pase el nombre del archivo como argumento
    if (argc < 2) {
        printf("%d\n",argc);
        printf("Uso: %s <ventas_demo.csv>\n", argv[0]);
        return 1;
    }

    // Leer el archivo CSV
    int size = 0;
    struct order *orders = read_csv(argv[1], &size);
    if (!orders) {
        printf("ERROR el nombre del archivo es incorrecto");
        return 1; // Error al leer el archivo
    }

    // Imprimir el número total de órdenes cargadas
    printf("Se cargaron %d órdenes.\n", size);

    // Inicializar el generador de números aleatorios
    srand(time(NULL));

    // Seleccionar e imprimir 5 órdenes al azar
    printf("\nÓrdenes seleccionadas al azar:\n");
    for (int i = 0; i < 5; i++) {
        int random_index = rand() % size; // Generar un índice aleatorio entre 0 y size-1
        printf("Orden %d (índice %d):\n", i + 1, random_index);
        printf("  Pizza ID: %d\n", orders[random_index].pizza_id);
        printf("  Nombre de la pizza: %s\n", orders[random_index].pizza_name);
        printf("  Cantidad: %d\n", orders[random_index].quantity);
        printf("  Precio total: %.2f\n", orders[random_index].total_price);
    }

    // Una prueba de la función pms que encuentra la pizza más vendida.
    char *mas_vendido = pms(&size, orders);
    printf("\n%s fue la pizza mas vendida\n", mas_vendido);
    free(mas_vendido); // pms y pls guardan los nombres en memoria dinámica, liberar tras usar para evitar contaminación.
    
    // Una prueba de la función pms que encuentra la pizza menos vendida.
    char *menos_vendido = pls(&size, orders);
    printf("\n%s fue la pizza menos vendida\n\n", menos_vendido);
    free(menos_vendido);
    

    //Una prueba de la función dms que encuentra la fecha mas recaudada.
    char *mayor_fecha_dinero = dms(&size, orders);
    printf("La fecha con mas recaudacion fue %s\n", mayor_fecha_dinero);
    free(mayor_fecha_dinero);

    //Una prueba de la función dls que encuentra la fecha menos recaudada.
    char *menor_fecha_dinero = dls(&size, orders);
    printf("La fecha con menor recaudacion fue %s\n", menor_fecha_dinero);
    free(menor_fecha_dinero);
    
    //Una prueba de la función dms que encuentra la fecha con más pizzas vendidas.
    char *mas_pizzas = dmsp(&size, orders);
    printf("La fecha con mas pizzas vendidas fue %s\n", mas_pizzas);
    free(mas_pizzas);

    //Una prueba de la función dms que encuentra la fecha con más pizzas vendidas.
    char *menos_pizzas = dlsp(&size, orders);
    printf("La fecha con menos pizzas vendidas fue %s\n", menos_pizzas);
    free(menos_pizzas);
    //Una prueba de la función que calcula el promedio de pizzas por orden 
    char *promedio_pizzas = apo(&size, orders);
    printf("%s pizzas\n", promedio_pizzas);
    free(promedio_pizzas);
    //Una prueba de la función que calcula el proedio de pizzas por día
    char *promedio_dia = apd(&size, orders);
    printf("%s pizzas\n", promedio_dia);
    free(promedio_dia);
    //Una prueba de la función que encuentra el ingrediente más vendido entre todas las ordenes.
    char *ingrediente_top = ims(&size, orders);
    printf("Ingrediente mas vendido: %s\n", ingrediente_top);
    free(ingrediente_top);
    //Una prueba de la función que muestra todas las categorías con su cantidad vendida.
    char *categorias = hp(&size, orders);
    printf("Pizzas vendidas por categoria:\n%s", categorias);
    free(categorias);


    // Liberar memoria
    free(orders);

    return 0;
}