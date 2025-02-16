/*
===============================================================================
File:                   battleship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          15.01.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      13.03.2024
Version:                1.0
Description:            This is the file in which exercice 1 must be implemented
                        User should be able to play a simplified battleship game
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE  10

int main(int argc, char *argv[]) {
    int board[BOARD_SIZE];
    int lives = 5;
    int ship_cases = 3;
    srand(time(NULL));

    // Generate three random positions for the ships
    for (int i = 0; i < ship_cases; i++) {
        int random;
        do {
            random = rand() % BOARD_SIZE;
        }
        while (board[random] == 2);
        board[random] = 2;
    }

    do {
        int attack;
        printf("Please select a position to attack between 0 and 9!\n");
        scanf("%d", &attack);
        if (attack < 0 || attack >= BOARD_SIZE) {
            printf("Invalid attack\n");
            continue;
        }
        if (board[attack] == 1) {
            printf("You already attacked this case\n");
            continue;
        }
        if (board[attack] == 2) {
            printf("HIT\n");
            ship_cases--;  // Decrement the number of ships
        } else {
            printf("MISS\n");
            lives--;
            if (lives == 0) {
                printf("YOU LOST\n");
                return EXIT_SUCCESS;
            }
        }
        // Update the board
        board[attack] = 1;
        printf("%d lives remaining, %d ships remaining\n", lives, ship_cases);
    }
    while (lives > 0 && ship_cases > 0);

    if (ship_cases == 0) {
        printf("YOU WON\n");
    } else {
        printf("YOU LOST\n");
    }

    return EXIT_SUCCESS;
}
