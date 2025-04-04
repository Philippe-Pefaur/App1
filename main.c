#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "utils.h"
#include "metrics.h"

int main(int argc, char *argv[])
{
    printf("Bienvenido al programa de analisis de ventas de la pizzería.\n");

    // Verificar que se pase el nombre del archivo como argumento
    if (argc < 3)
    {
        printf("Uso: %s <ventas.csv> <métrica1> [<métrica2> ...]\n", argv[0]);
        return 1;
    }

    // Leer el archivo CSV
    int size = 0;
    struct order *orders = read_csv(argv[1], &size);
    if (!orders)
    {
        printf("ERROR: No se pudo leer el archivo %s\n", argv[1]);
        return 1; // Error al leer el archivo
    }

    // Imprimir el número total de órdenes cargadas
    printf("Se cargaron %d ordenes.\n", size);

    // Procesar cada métrica pasada como argumento
    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "pms") == 0)
        {
            char *mas_vendido = pms(&size, orders);
            printf("\n%s fue la pizza mas vendida.\n", mas_vendido);
            free(mas_vendido);
        }
        else if (strcmp(argv[i], "pls") == 0)
        {
            char *menos_vendido = pls(&size, orders);
            printf("\n%s fue la pizza menos vendida.\n", menos_vendido);
            free(menos_vendido);
        }
        else if (strcmp(argv[i], "dms") == 0)
        {
            char *mayor_fecha_dinero = dms(&size, orders);
            printf("\nLa fecha con más recaudacion fue %s.\n", mayor_fecha_dinero);
            free(mayor_fecha_dinero);
        }
        else if (strcmp(argv[i], "dls") == 0)
        {
            char *menor_fecha_dinero = dls(&size, orders);
            printf("\nLa fecha con menor recaudacion fue %s.\n", menor_fecha_dinero);
            free(menor_fecha_dinero);
        }
        else if (strcmp(argv[i], "dmsp") == 0)
        {
            char *mas_pizzas = dmsp(&size, orders);
            printf("\nLa fecha con mas pizzas vendidas fue %s.\n", mas_pizzas);
            free(mas_pizzas);
        }
        else if (strcmp(argv[i], "dlsp") == 0)
        {
            char *menos_pizzas = dlsp(&size, orders);
            printf("\nLa fecha con menos pizzas vendidas fue %s.\n", menos_pizzas);
            free(menos_pizzas);
        }
        else if (strcmp(argv[i], "apo") == 0)
        {
            char *promedio_pizzas = apo(&size, orders);
            printf("\n%s\n", promedio_pizzas);
            free(promedio_pizzas);
        }
        else if (strcmp(argv[i], "apd") == 0)
        {
            char *promedio_dia = apd(&size, orders);
            printf("\n%s\n", promedio_dia);
            free(promedio_dia);
        }
        else if (strcmp(argv[i], "ims") == 0)
        {
            char *ingrediente_top = ims(&size, orders);
            printf("\nIngrediente mas vendido: %s\n", ingrediente_top);
            free(ingrediente_top);
        }
        else if (strcmp(argv[i], "hp") == 0)
        {
            char *categorias = hp(&size, orders);
            printf("\nPizzas vendidas por categoria:\n%s", categorias);
            free(categorias);
        }
        else
        {
            printf("\nMetrica desconocida: %s\n", argv[i]);
        }
    }

    // Liberar memoria
    free(orders);

    return 0;
}