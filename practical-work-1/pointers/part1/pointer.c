/*
===============================================================================
File:                   exploration_sol.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          15.01.2024
Modification Author:    Edison Sahitaj, Nicolet Victor
Modification Date:      12.03.2024
Version:                1.0
Description:            In this file you should iterate on an array without using
                        direct index.
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int var = 1;
    int *ptrvar = &var;
    printf("Affichage de l'addresse pointee par le pointeur : %p\n", &ptrvar);
    printf("Affichage de la valeur de la variable en dereferencantle pointeur : %d\n", *ptrvar);
    var = 2;
    printf("Modification de la variable de base : %d\n", var);
    printf("Affichage de la valeur de la variable en dereferencant le pointeur : %d\n", *ptrvar);
    *ptrvar = 10;
    printf("Modification de la valeur de la variable à travers le pointeur : %d\n", var);
    printf("Affichage de la valeur de la variable de base : %d\n\n", var);
}
