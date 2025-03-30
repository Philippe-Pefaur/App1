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

    // Una pureba de la función pms que encuentra la pizza más vendida.
    char *mas_vendido = pms(&size, orders);
    printf("\n%s fue la pizza más vendida\n", mas_vendido);

    // Liberar memoria
    free(orders);

    return 0;
}