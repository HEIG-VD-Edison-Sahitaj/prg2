/*
===============================================================================
File:                   exploration_sol.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          15.01.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      13.03.2024
Version:                1.0
Description:            In this file you should iterate on an array without using
                        direct index.
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int tab[10];
    int *ptr = tab;
    for (size_t i = 0; i < 10; i++) {
        printf("%d ", *ptr);
    }
    printf("\n");
    for (size_t i = 0; i < 10; i++) {
        *ptr = i;
        printf("%d ", *ptr);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
