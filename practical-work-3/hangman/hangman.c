/*
===============================================================================
File:                   hangman.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          07.03.2024
Modification Author:    Sahitaj Edison, Nicolet Victor
Modification Date:      09.04.2024
Version:                1.0
Description:            This is the file in which exercice 2 must be implemented
                        User should be able to play a hangman game
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define LIFE_LIMIT 0            /**< Minimum number of lives allowed */
#define WORD_GUESSED 0          /**< Return code indicating that the word has been guessed */
#define MORE_THAN_ONE_CHARACTER 1  /**< Constant indicating a word guess (as opposed to single letter guess) */
#define LIVES_DECREMENT 2       /**< Number of lives to decrement upon an incorrect word guess */
#define ALREADY_GUESSED 2       /**< Return code indicating that the guessed letter has already been tried */
#define LETTER_INCORRECT 3      /**< Return code indicating an incorrect letter guess */
#define WORD_INCORRECT 4        /**< Return code indicating an incorrect word guess */
#define NOT_IN_ALPHABET 5       /**< Return code indicating input that is not a letter */
#define NOT_GUESSED 6           /**< Return code indicating that a letter has not been guessed */
#define ALL_GUESSED 7           /**< Return code indicating that all letters have been guessed */
#define GUESSED 8               /**< Return code indicating a successful letter guess */
#define DEFAULT_LIVES 10        /**< Default number of lives */
#define MAX_INPUT_LENGTH 100    /**< Maximum length of user input */

static char *DICTIONNARY[] = {
    "chien",
    "table",
    "pierre",
    "dictionnaire"
};

/**
 * @brief Picks a random word from the dictionary.
 *
 * @return A random word.
 */
char *pick_random_word() {
    srand(time(NULL));
    int random_index = rand() % (sizeof(DICTIONNARY) / sizeof(DICTIONNARY[0]));
    return DICTIONNARY[random_index];
}

/**
 * @brief Displays the word with the guessed letters.
 *
 * @param word The word to display.
 * @param guessed_letters The letters that have been guessed.
 */
void display_word(const char *word, const char *guessed_letters) {
    for (int i = 0; word[i]; i++) {
        printf("%c", strchr(guessed_letters, word[i]) ? word[i] : '-'); // Print the letter if it has been guessed, otherwise print a dash
    }
    printf("\n"); // Print a newline after displaying the word
}

/**
 * @brief Prints the game state.
 *
 * @param word The word to guess.
 * @param guessed_letters The letters that have been guessed.
 * @param lives The number of lives left.
 */
void print_game_state(const char *word, const char *guessed_letters, int lives) {
    printf("Lifes: %d\n", lives);
    printf("Tried letters: %s\n", guessed_letters);
}

/**
 * @brief Checks if all the letters of the word have been guessed.
 *
 * @param word The word to guess.
 * @param guessed_letters The letters that have been guessed.
 * @return 1 if all the letters have been guessed, 0 otherwise.
 */
int all_letters_guessed(const char *word, const char *guessed_letters) {
    for (int i = 0; word[i]; i++) {
        if (!strchr(guessed_letters, word[i])) {
            return NOT_GUESSED;
        }
    }
    return ALL_GUESSED;
}

/**
 * @brief Counts the number of occurrences of a letter in a word.
 *
 * @param word The word to check.
 * @param letter The letter to count.
 * @return The number of occurrences of the letter in the word.
 */
int count_occurrences(const char *word, char letter) {
    int count = 0;
    for (int i = 0; word[i]; i++) {
        if (word[i] == letter) {
            count++;
        }
    }
    return count;
}

/**
 * @brief Processes a single letter guess.
 *
 * @param guessed_letters The letters that have been guessed.
 * @param word The word to guess.
 * @param input The input to process.
 * @param lives The number of lives left.
 * @return The result of the guess.
 */
int process_single_letter_guess(char *guessed_letters, const char *word, char *input, int *lives) {
    if (!isalpha(input[0])) {
        return NOT_IN_ALPHABET;
    }
    if (strchr(guessed_letters, input[0])) {
        return ALREADY_GUESSED;
    }

    strncat(guessed_letters, input, 1);

    if (!strchr(word, input[0])) {
        (*lives)--;
        return LETTER_INCORRECT;
    }
    return GUESSED;
}

/**
 * @brief Processes a word guess.
 *
 * @param word The word to guess.
 * @param input The input to process.
 * @param lives The number of lives left.
 * @return The result of the guess.
 */
int process_word_guess(const char *word, char *input, int *lives) {
    if (strcmp(word, input) == 0) {
        return WORD_GUESSED;
    } else {
        (*lives) -= LIVES_DECREMENT;
        return WORD_INCORRECT;
    }
}

int main(int argc, char **argv) {
    char *word = pick_random_word();
    char guessed_letters[MAX_INPUT_LENGTH] = "";
    int lives = DEFAULT_LIVES;
    if (argc > 2 && strcmp(argv[1], "--lifes") == 0) {
        lives = atoi(argv[2]);
    }

    while (lives > LIFE_LIMIT) {
        print_game_state(word, guessed_letters, lives);
        display_word(word, guessed_letters);

        char input[MAX_INPUT_LENGTH];
        printf("Guess a letter or a word: ");
        scanf("%s", input);
        for (int i = 0; input[i]; i++) {
            input[i] = tolower(input[i]);
        }

        int result;
        if (strlen(input) > MORE_THAN_ONE_CHARACTER) {
            result = process_word_guess(word, input, &lives);
            if (result == WORD_GUESSED) {
                printf("GG !! You win \\o/\n");
                break;
            }
        } else {
            result = process_single_letter_guess(guessed_letters, word, input, &lives);
        }

        switch (result) {
        case GUESSED:
            printf("There is %d occurence of a in the word!\n", count_occurrences(word, input[0]));
            break;
        case ALREADY_GUESSED:
            printf("%c has already been tried.\n", input[0]);
            break;
        case LETTER_INCORRECT:
            printf("%c is not in the word...\n", input[0]);
            break;
        case WORD_INCORRECT:
            printf("%s isn't the word !\n", input);
            break;
        case NOT_IN_ALPHABET:
            printf("%c is not a letter.\n", input[0]);
            break;
        }
        if (all_letters_guessed(word, guessed_letters) == ALL_GUESSED) {
            printf("GG !! You win \\o/\n");
            break;
        }
    }
    if (lives <= LIFE_LIMIT) {
        printf("You lose... The word was %s\n", word);
    }
}
