# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "data_structures.h"

char* pms(int *size, struct order *orders) {
    int i;
    char nombres[50][100] = {0};
    int sumas[50] = {0};
    int index = 0;

    for (i = 0; i < *size; i++) {
        int j;
        int control = 0;
        for (j = 0; j <= index; j++)
            if (strcmp(nombres[j], orders[i].pizza_name) == 0) {
                sumas[j] += orders[i].quantity;
                control = 1;
                break;
            }
        if (!control) {
            strcpy(nombres[index], orders[i].pizza_name);
            sumas[index] = orders[i].quantity;
            index++;
        }   
    }

    int max_index = 0;
    for (i = 1; i < index; i++) {
        if (sumas[i] > sumas[max_index]) {
            max_index = i;
        }
    }

    char *mas_vendido = (char*)malloc(100 * sizeof(char));
    if (mas_vendido != NULL) {
        strcpy(mas_vendido, nombres[max_index]);
    } 
    else {
        printf("ERROR al alocar memoria.");
        return NULL;
    }

    return mas_vendido;
}