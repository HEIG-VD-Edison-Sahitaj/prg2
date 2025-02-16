/*
===============================================================================
File:                   better_grades.c
Course:                 PRG2
Year:                   2024
Author:                 Clément Dieperink
Creation Date:          15.01.2024
Modification Author:    Sahitaj Edison, Nicolet Victor
Modification Date:      26.03.2024
Version:                1.0
Description:            This file implements a more advanced grades management
                        tool which should be able to handle several course
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SUCCESS 0
#define ERROR_GRADE_ARRAY_FULL -1
#define ERROR_MEMORY_REALLOCATION -4
#define MAX_NAME_SIZE 10

#define MAXIMAL_GRADE 6.0
#define MINIMAL_GRADE 1.0

/**
 *
 * @param sub
 * @param grades
 * @param max_grades
 * @param n_sub
 */
void print_sub_grades(char **sub, float *grades, const int max_grades, const int n_sub) {
    for (int i = 0; i < n_sub; i++) {
        printf("%s: ", sub[i]);
        int has_grade = 0;
        for (int j = 0; j < max_grades; j++) {
            if (grades[i * max_grades + j] != 0) {
                if (has_grade) {
                    printf(", ");
                }
                printf("%.1f", grades[i * max_grades + j]);
                has_grade = 1;
            }
        }
        if (!has_grade) {
            printf("No grades");
        }
        printf("\n");
    }
}

/**
 *
 * @param grade
 * @return
 */
bool is_valid_grade(float grade) {
    return grade >= MINIMAL_GRADE && grade <= MAXIMAL_GRADE;
}

int add_grade(char **subjects, float *grades, const int max_grades, const int n_sub) {
    char subject[MAX_NAME_SIZE];
    float grade;
    do {
        printf("Enter the name of the subject: ");
        scanf("%s", subject);
        for (int i = 0; i < n_sub; i++) {
            if (strcmp(subject, subjects[i]) == 0) {
                printf("Enter the grade: ");
                scanf("%f", &grade);
                if (!is_valid_grade(grade)) {
                    printf("Grade is not valid.\n");
                    continue;
                }
                for (int j = 0; j < max_grades; j++) {
                    if (grades[i * max_grades + j] == 0) {
                        grades[i * max_grades + j] = grade;
                        return SUCCESS;
                    }
                }
                return ERROR_GRADE_ARRAY_FULL;
            }
        }
        printf("Subject not found.\n");
    }
    while (true);
}

void swap(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

int delete_grade(char **subjects, float *grades, const int max_grades, const int n_sub) {
    char subject[MAX_NAME_SIZE];
    do {
        printf("Enter the name of the subject: ");
        scanf("%s", subject);
        for (int i = 0; i < n_sub; i++) {
            if (strcmp(subject, subjects[i]) == 0) {
                int grade_position;
                do {
                    printf("Enter the grade position: ");
                    scanf("%d", &grade_position);
                    if (grades[i * max_grades + grade_position - 1] != 0) {
                        grades[i * max_grades + grade_position - 1] = 0;
                        for (int j = grade_position; j < max_grades; j++) {
                            swap(&grades[i * max_grades + j - 1], &grades[i * max_grades + j]);
                        }
                        return SUCCESS;
                    } else {
                        printf("Position is not valid.\n");
                    }
                }
                while (true);
            }
        }
        printf("Subject not found.\n");
    }
    while (true);
}

int modify_grade(char **subjects, float *grades, const int max_grades, const int n_sub) {
    char subject[MAX_NAME_SIZE];
    do {
        printf("Enter the name of the subject: ");
        scanf("%s", subject);
        for (int i = 0; i < n_sub; i++) {
            if (strcmp(subject, subjects[i]) == 0) {
                int grade_position;
                do {
                    printf("Enter the grade position: ");
                    scanf("%d", &grade_position);
                    if (grades[i * max_grades + grade_position - 1] != 0) {
                        float grade;
                        do {
                            printf("Enter the grade value: ");
                            scanf("%f", &grade);
                            if (!is_valid_grade(grade)) {
                                printf("Grade is not valid.\n");
                            }
                        }
                        while (!is_valid_grade(grade));
                        grades[i * max_grades + grade_position - 1] = grade;
                        return SUCCESS;
                    } else {
                        printf("Position is not valid.\n");
                    }
                }
                while (true);
            }
        }
        printf("Subject not found.\n");
    }
    while (true);
}

int swap_grade(char **subjects, float *grades, const int max_grades, const int n_sub) {
    char subject[MAX_NAME_SIZE];
    int subject_found = 0;
    do {
        printf("Enter the name of the subject: ");
        scanf("%s", subject);
        for (int i = 0; i < n_sub; i++) {
            if (strcmp(subject, subjects[i]) == 0) {
                subject_found = 1;
                int has_grade = 0;
                for (int j = 0; j < max_grades; j++) {
                    if (grades[i * max_grades + j] != 0) {
                        has_grade = 1;
                        break;
                    }
                }
                if (!has_grade) {
                    printf("Array is empty.\n");
                    break;
                }
                int grade_position1, grade_position2;
                do {
                    printf("Enter the two grades positions to swap: ");
                    scanf("%d %d", &grade_position1, &grade_position2);
                    if (grades[i * max_grades + grade_position1 - 1] != 0 && grades[i * max_grades + grade_position2 - 1] != 0) {
                        swap(&grades[i * max_grades + grade_position1 - 1], &grades[i * max_grades + grade_position2 - 1]);
                        return SUCCESS;
                    } else {
                        printf("Position is not valid.\n");
                    }
                }
                while (true);
            }
        }
        if (!subject_found) {
            printf("Subject not found.\n");
        }
    }
    while (!subject_found);
}

/**
 * @brief Computes the average grade for each subject.
 *
 * This function calculates and prints the average grade for each subject.
 *
 * @param subjects Pointer to an array of strings representing the names of subjects.
 * @param grades Pointer to an array of floating-point numbers representing the grades.
 * @param max_grades Maximum number of grades per subject in the `grades` array.
 * @param n_sub Total number of subjects.
 */
void compute_average(char **subjects, float *grades, const int max_grades, const int n_sub) {
    for (int i = 0; i < n_sub; i++) {
        double sum = 0;
        int count = 0;
        for (int j = 0; j < max_grades; j++) {
            if (grades[i * max_grades + j] != 0) {
                sum += grades[i * max_grades + j];
                count++;
            } else {
                break;
            }
        }
        if (count == 0) {
            printf("%s: No grades\n", subjects[i]);
        } else {
            printf("%s: %.1f\n", subjects[i], sum / count);
        }
    }
}

/**
 * @brief Modifies the name of a subject.
 *
 * This function prompts the user to enter the name of a subject to be modified and a new name for it.
 * It then modifies the name of the specified subject.
 *
 * @param subjects Pointer to an array of strings representing the names of subjects.
 * @param n_sub Total number of subjects.
 * @return An integer indicating the status of the operation:
 *         - SUCCESS (0) if the subject name was successfully modified.
 */
int modify_subject_name(char **subjects, const int n_sub) {
    char subject[MAX_NAME_SIZE];
    do {
        printf("Enter the subject name: ");
        scanf("%s", subject);
        for (int i = 0; i < n_sub; i++) {
            if (strcmp(subject, subjects[i]) == 0) {
                char subject_change[MAX_NAME_SIZE];
                printf("Enter the name for the subject: ");
                scanf("%s", subject_change);
                strcpy(subjects[i], subject_change);
                return SUCCESS;
            }
        }
        printf("Subject not found.\n");
    }
    while (true);
}

/**
 * @brief Adds a new subject.
 *
 * This function adds a new subject to the `subjects` array and initializes its corresponding grades in the `grades` array with zeros.
 *
 * @param subjects Pointer to a pointer to an array of strings representing the names of subjects.
 * @param grades Pointer to a pointer to an array of floating-point numbers representing the grades.
 * @param max_grades Maximum number of grades per subject in the `grades` array.
 * @param n_sub Pointer to an integer storing the total number of subjects. Will be incremented after adding the new subject.
 * @return An integer indicating the status of the operation:
 *         - SUCCESS (0) if the subject was successfully added.
 *         - ERROR_MEMORY_REALLOCATION (1) if memory reallocation failed.
 */
int add_a_subject(char ***subjects, float **grades, int max_grades, int *n_sub) {

    (*n_sub)++;

    *subjects = (char **)realloc(*subjects, (*n_sub) * sizeof(char *));
    if (*subjects == NULL) {
        printf("Memory allocation failed.\n");
        return ERROR_MEMORY_REALLOCATION;
    }

    (*subjects)[(*n_sub) - 1] = (char *)malloc(MAX_NAME_SIZE * sizeof(char));
    if ((*subjects)[(*n_sub) - 1] == NULL) {
        printf("Memory allocation failed.\n");
        free(*subjects);
        return ERROR_MEMORY_REALLOCATION;
    }

    *grades = (float *)realloc(*grades, (*n_sub) * max_grades * sizeof(float));
    if (*grades == NULL) {
        printf("Memory allocation failed.\n");
        for (int i = 0; i < *n_sub; i++) {
            free((*subjects)[i]);
        }
        free(*subjects);
        return ERROR_MEMORY_REALLOCATION;
    }

    int start_index = (*n_sub - 1) * max_grades;
    int end_index = *n_sub * max_grades;

    memset(*grades + start_index, 0, (end_index - start_index) * sizeof(float));

    char new_subject[MAX_NAME_SIZE];
    printf("Enter the name for the subject: ");
    scanf("%s", new_subject);

    strcpy((*subjects)[(*n_sub) - 1], new_subject);

    return SUCCESS;
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <N_SUBJECT> <MAX_GRADES>\n", argv[0]);
        return 1;
    }

    int n_subjects = atoi(argv[1]);
    int max_grades = atoi(argv[2]);

    char **subjects = (char **)malloc(n_subjects * sizeof(char *));
    if (subjects == NULL) {
        printf("Allocation de mémoire pour les noms de matières a échoué.\n");
        return 1;
    }

    for (int i = 0; i < n_subjects; i++) {
        subjects[i] = (char *)malloc(MAX_NAME_SIZE * sizeof(char));
        if (subjects[i] == NULL) {
            printf("Allocation de mémoire pour un nom de matière a échoué.\n");
            free(subjects);
            return 1;
        }
    }

    float *grades = (float *)calloc(n_subjects * max_grades, sizeof(float));
    if (grades == NULL) {
        printf("Memory allocation failed.\n");
        free(subjects);
        return 1;
    }

    // Demander les noms des branches à l'utilisateur
    for (int i = 0; i < n_subjects; i++) {
        printf("Enter the name for subject %d:", i + 1);
        scanf(" %s", subjects[i]);
    }

    int choice;
    do {
        printf("\n");
        printf("1: Add a grade\n");
        printf("2: Delete a grade\n");
        printf("3: Modify a grade\n");
        printf("4: Swap a grade\n");
        printf("5: Compute average\n");
        printf("6: Modify subject name\n");
        printf("7: Add a subject\n");
        printf("8: Quit\n\n");

        print_sub_grades(subjects, grades, max_grades, n_subjects);

        printf("\n\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            int add = add_grade(subjects, grades, max_grades, n_subjects);
            if (add == ERROR_GRADE_ARRAY_FULL) {
                printf("Error: Grade array is full.\n");
            } else if (add == ERROR_MEMORY_REALLOCATION) {
                printf("Error: Memory reallocation failed.\n");
            }
            break;
        case 2:
            int del = delete_grade(subjects, grades, max_grades, n_subjects);
            break;
        case 3:
            int mod = modify_grade(subjects, grades, max_grades, n_subjects);
            break;
        case 4:
            int swap = swap_grade(subjects, grades, max_grades, n_subjects);
            break;
        case 5:
            compute_average(subjects, grades, max_grades, n_subjects);
            break;
        case 6:
            int mod_sub = modify_subject_name(subjects, n_subjects);
            break;
        case 7:
            int add_sub = add_a_subject(&subjects, &grades, max_grades, &n_subjects);
            if (add_sub == ERROR_MEMORY_REALLOCATION) {
                printf("Error: Memory reallocation failed.\n");
            }
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    while (choice != 6);
    for (int i = 0; i < n_subjects; i++) {
        free(subjects[i]);
    }
    free(subjects);
    free(grades);
}
