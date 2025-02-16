/*
===============================================================================
File:                   battleship.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          05.03.2024
Modification Author:    Sahitaj Edison, Nicolet Victor
Modification Date:      09.04.2024
Version:                1.0
Description:            This is the file in which exercice 1 must be implemented
                        User should be able to play a simplified battleship game
                        using only 1 32bits variable to store all the game datas
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 12
#define MAX_LIVES 6
#define MAX_SHIPS 6

/**
 * @brief Displays the game menu, showing the remaining lives and ships.
 *
 * @param game_data The game data packed into a 32-bit integer. The number of lives is stored in bits 27-24 and the number of ships is stored in bits 31-28.
 */
void display_menu(unsigned int game_data) {
    // Extract the number of lives from bits 27-24
    int lives = (game_data >> 24) & 0xF;

    // Extract the number of ships from bits 31-28
    int ships = (game_data >> 28) & 0xF;
    printf("%d lifes remaining, %d ships remaining\n", lives, ships);
    printf("Please select a position to attack between 0 and %d!\n", BOARD_SIZE - 1);
}

/**
 * @brief Checks if a given position is valid.
 *
 * @param position The position to check.
 * @return int Returns 1 if the position is valid (i.e., within the range [0, BOARD_SIZE)), and 0 otherwise.
 */
int is_valid_position(int position) {
    return (position >= 0 && position < BOARD_SIZE);
}

/**
 * @brief Checks if a given position has been attacked.
 *
 * @param game_data The game data packed into a 32-bit integer. The attack status of each position is stored in bits 23-0, with the bit at position (23 - n) representing the attack status of position n.
 * @param position The position to check.
 * @return int Returns 1 if the position has been attacked, and 0 otherwise.
 */
int is_position_attacked(unsigned int game_data, int position) {
    return (game_data & (1 << (23 - position))) != 0;
}

/**
 * @brief Checks if a given position contains a ship.
 *
 * @param game_data The game data packed into a 32-bit integer. The ship status of each position is stored in bits 11-0, with the bit at position (11 - n) representing the ship status of position n.
 * @param position The position to check.
 * @return int Returns 1 if the position contains a ship, and 0 otherwise.
 */
int is_ship_position(unsigned int game_data, int position) {
    return (game_data & (1 << (11 - position))) != 0;
}

/**
 * @brief Attacks a given position on the game board.
 *
 * @param game_data The game data packed into a 32-bit integer. The attack status of each position is stored in bits 23-0, with the bit at position (23 - n) representing the attack status of position n. The number of lives is stored in bits 27-24 and the number of ships is stored in bits 31-28.
 * @param position The position to attack.
 * @return unsigned int Returns the updated game data after the attack.
 */
unsigned int attack_position(unsigned int game_data, int position) {
    game_data |= (1 << (23 - position));

    // Check if the position contains a ship
    if (is_ship_position(game_data, position)) {
        // decrement the number of ships and print "HIT"
        game_data -= (1 << 28);
        printf("HIT\n");
    } else {
        // decrement the number of lives and print "MISS"
        game_data -= (1 << 24);
        printf("MISS\n");
    }

    return game_data;
}

/**
 * @brief Initializes the positions of the ships on the game board.
 *
 * @param game_data The game data packed into a 32-bit integer. The ship status of each position is stored in bits 11-0, with the bit at position (11 - n) representing the ship status of position n. The number of ships is stored in bits 31-28.
 * @return unsigned int Returns the updated game data after initializing the ship positions.
 */
unsigned int initialize_ship_positions(unsigned int game_data) {
    // Initialize the random number generator
    srand(time(NULL));

    for (int i = 0; i < MAX_SHIPS; i++) {
        // Generating random positions until we find one that doesn't already contain a ship
        while (1) {
            int position = rand() % BOARD_SIZE;
            if (!is_ship_position(game_data, position)) {
                game_data |= (1 << (11 - position));
                break;
            }
        }
    }

    return game_data;
}

int main() {
    unsigned int game_data = 0; // Initialize game_data to 0

    // Set lives and ships using bitwise OR and shift
    game_data |= MAX_LIVES << 24; // Set lives in bits 27-24
    game_data |= MAX_SHIPS << 28; // Set ships in bits 31-28

    srand(time(NULL));

    game_data = initialize_ship_positions(game_data);

    while (1) {
        display_menu(game_data);

        int position = 0;
        int ret = 0;

        do {
            printf("Enter a position: ");
            ret = scanf("%d", &position);
            while (getchar() != '\n'); // clear input buffer
            if (ret != 1) {
                printf("Invalid input. Please enter a number.\n");
            } else if (!is_valid_position(position)) {
                printf("Invalid position\n");
                ret = 0; // force the loop to continue
            } else if (is_position_attacked(game_data, position)) {
                printf("Already attacked this position\n");
                ret = 0; // force the loop to continue
            }
        }
        while (ret != 1);

        // Attack the entered position
        game_data = attack_position(game_data, position);

        // Check if the game is over
        if (((game_data >> 24) & 0xF) == 0) {
            printf("YOU LOSE\n");
            break;
        } else if (((game_data >> 28) & 0xF) == 0) {
            printf("YOU WIN\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
