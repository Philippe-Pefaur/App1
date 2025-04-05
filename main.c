#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structures.h"
#include "utils.h"
#include "metrics.h"

int main(int argc, char *argv[])
{
    printf("------------------------------------\nBienvenido al programa de analisis de ventas de la pizzeria.\n");

    // Verificar que se pase el nombre del archivo como argumento
    if (argc < 3)
    {
        printf("Uso: %s <ventas.csv> <metrica1> [<metrica2> ...]\n", argv[0]);
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

    // Arreglo donde guardar los punteros y formato de las funciones a ejecutrar
    struct metricas arreglo_metricas[10] = {
        {pms, "\n%s fue la pizza mas vendida.\n"},
        {pls, "\n%s fue la pizza menos vendida.\n"},
        {dms, "\nLa fecha con mas recaudacion fue %s.\n"},
        {dls, "\nLa fecha con menor recaudacion fue %s.\n"},
        {dmsp, "\nLa fecha con mas pizzas vendidas fue %s.\n"},
        {dlsp, "\nLa fecha con menos pizzas vendidas fue %s.\n"},
        {apo, "\n%s\n"},
        {apd, "\n%s\n"},
        {ims, "\nIngrediente mas vendido: %s\n"},
        {hp, "\nPizzas vendidas por categoria:\n%s"}
    };

    // Arreglo metricas a ejecutar
    struct metricas ejecutar_metricas[10] = {0};

    // Procesar cada métrica pasada como argumento
    int indice = 0;
    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "pms") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[0];
            indice++;
        }
        else if (strcmp(argv[i], "pls") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[1];
            indice++;
        }
        else if (strcmp(argv[i], "dms") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[2];
            indice++;
        }
        else if (strcmp(argv[i], "dls") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[3];
            indice++;
        }
        else if (strcmp(argv[i], "dmsp") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[4];
            indice++;
        }
        else if (strcmp(argv[i], "dlsp") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[5];
            indice++;
        }
        else if (strcmp(argv[i], "apo") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[6];
            indice++;
        }
        else if (strcmp(argv[i], "apd") == 0)
        {;
            ejecutar_metricas[indice] = arreglo_metricas[7];
            indice++;
        }
        else if (strcmp(argv[i], "ims") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[8];
            indice++;
        }
        else if (strcmp(argv[i], "hp") == 0)
        {
            ejecutar_metricas[indice] = arreglo_metricas[9];
            indice++;
        }
        else {
            printf("\nMetrica desconocida: %s\n", argv[i]);
        }
    }

    // Ejecutar funciones pedidas:
    for (int i = 0; i < indice; i++){
        char *resultado = (ejecutar_metricas[i].funcion)(&size, orders);
        printf(ejecutar_metricas[i].formateo, resultado);
        free(resultado);
    }

    // Liberar memoria
    free(orders);
    
    printf("------------------------------------\n"); // Imprimir línea que marca el fin de las métricas imprimidas por pantalla
    return 0;
}