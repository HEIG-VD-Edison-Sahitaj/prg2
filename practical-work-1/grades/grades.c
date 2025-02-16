/*
===============================================================================
File:                   grades.c
Course:                 PRG2
Year:                   2024
Author:                 Clément Dieperink
Creation Date:          15.01.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      13.03.2024
Version:                1.0
Description:            This file implements a simple grade management for
                        one course.
===============================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_GRADES 10
#define SUCCESS 0
#define ERROR_GRADE_ARRAY_FULL -1
#define ERROR_NO_GRADES -2
#define ERROR_INVALID_NUMBER_OF_GRADES -3

/*
* Function: is_valid_grade
* -------------------------
* Checks if a grade is valid.
*
* grade: the grade to check
*
* returns: true if the grade is valid, false otherwise
*/
bool is_valid_grade(double grade) {
    return grade >= 1 && grade <= 6;
}

/*
* Function: print_grades
* -------------------------
* Prints the grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: void
*/
void print_grades(double grades[], int num_grades) {
    printf("Grades: ");
    for (int i = 0; i < num_grades; i++) {
        if (i == num_grades - 1) {
            printf("%.1lf", grades[i]);
        } else {
            printf("%.1lf, ", grades[i]);
        }
    }
    printf("\n");
}


/*
* Function: swap
* -------------------------
* Swaps two values.
*
* a: the first value
* b: the second value
*
* returns: void
*/
void swap(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

/*
* Function: add_grade
* -------------------------
* Adds a grade to the array of grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: 0 if the grade was added successfully, -1 if the array is full
*/
int add_grade(double grades[], int *num_grades) {
    if (*num_grades >= MAX_GRADES) {
        return ERROR_GRADE_ARRAY_FULL;
    }

    double new_grade;
    printf("Enter a new grade: ");
    scanf("%lf", &new_grade);

    while (!is_valid_grade(new_grade)) {
        printf("Invalid grade. Please enter a grade between 1 and 6: ");
        scanf("%lf", &new_grade);
    }

    grades[*num_grades] = new_grade;
    (*num_grades)++;

    return SUCCESS;
}

/*
* Function: delete_grade
* -------------------------
* Deletes a grade from the array of grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: 0 if the grade was deleted successfully, -2 if there are no grades
*/
int delete_grade(double grades[], int *num_grades) {
    if (*num_grades == 0) {
        return ERROR_NO_GRADES;
    }

    int index_to_delete;
    do {
        scanf("%d", &index_to_delete);
        if (index_to_delete < 1 || index_to_delete > *num_grades)
            printf("Invalid index. Please enter a number between 1 and %d: ", *num_grades);
    }
    while (index_to_delete < 1 || index_to_delete > *num_grades);

    for (int i = index_to_delete - 1; i < *num_grades - 1; i++) {
        grades[i] = grades[i + 1];
    }
    (*num_grades)--;

    return SUCCESS;
}

/*
* Function: modify_grade
* -------------------------
* Modifies a grade in the array of grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: 0 if the grade was modified successfully, -2 if there are no grades
*/
int modify_grade(double grades[], int *num_grades) {
    if (*num_grades == 0) {
        return ERROR_NO_GRADES;
    }
    int index_to_modify;
    double new_grade;
    do {
        scanf("%d", &index_to_modify);
        if (index_to_modify < 1 || index_to_modify > *num_grades) {
            printf("Invalid index. Please enter a number between 1 and %d: ", *num_grades);
            continue;
        }
        do {
            scanf("%lf", &new_grade);
            if (!is_valid_grade(new_grade))
                printf("Invalid grade. Please enter a grade between 1 and 6: ");
        }
        while (!is_valid_grade(new_grade));
    }
    while (index_to_modify < 1 || index_to_modify > *num_grades || !is_valid_grade(new_grade));
    {
        grades[index_to_modify - 1] = new_grade;
    }

    return SUCCESS;
}

/*
* Function: swap_grades
* -------------------------
* Swaps two grades in the array of grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: 0 if the grades were swapped successfully, -3 if there are not enough grades
*/
int swap_grades(double grades[], int *num_grades) {
    if (*num_grades < 2) {
        return ERROR_INVALID_NUMBER_OF_GRADES;
    }
    int index1, index2;
    do {
        scanf("%d %d", &index1, &index2);
        if (index1 < 1 || index1 > *num_grades || index2 < 1 || index2 > *num_grades)
            printf("Invalid index. Please enter two numbers between 1 and %d: ", *num_grades);
    }
    while (index1 < 1 || index1 > *num_grades || index2 < 1 || index2 > *num_grades);
    {
        swap(&grades[index1 - 1], &grades[index2 - 1]);
    }

    return SUCCESS;
}

/*
* Function: compute_average
* -------------------------
* Computes the average of the grades.
*
* grades: the array of grades
* num_grades: the number of grades
*
* returns: the average of the grades, -2 if there are no grades
*/
double compute_average(double grades[], int *num_grades) {
    if (num_grades == 0) {
        return ERROR_NO_GRADES;
    }
    double sum = 0;
    for (int i = 0; i < *num_grades; i++) {
        sum += grades[i];
    }
    return sum / *num_grades;
}

int main(int argc, char *argv[]) {
    double grades[MAX_GRADES];
    int num_grades = 0;
    int choice;
    do {
        printf("1: Add a grade\n");
        printf("2: Delete a grade\n");
        printf("3: Modify a grade\n");
        printf("4: Swap two grades\n");
        printf("5: Compute average\n");
        printf("6: Quit\n");
        print_grades(grades, num_grades);
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            int add = add_grade(grades, &num_grades);
            if (add == ERROR_GRADE_ARRAY_FULL) {
                printf("Error: Grade array is full.\n");
            }
            break;
        case 2:
            int delete = delete_grade(grades, &num_grades);
            if (delete == ERROR_NO_GRADES) {
                printf("Error: No grades to delete.\n");
            }
            break;
        case 3:
            int modify = modify_grade(grades, &num_grades);
            if (modify == ERROR_NO_GRADES) {
                printf("Error: No grades to modify.\n");
            }
            break;
        case 4:
            int swap = swap_grades(grades, &num_grades);
            if (swap == ERROR_INVALID_NUMBER_OF_GRADES) {
                printf("Error: Not enough grades to swap.\n");
            }
            break;
        case 5:
            double average = compute_average(grades, &num_grades);
            if (average == ERROR_NO_GRADES) {
                printf("Error: No grades to compute average.\n");
            } else {
                printf("The average is %.1lf\n", average);
            }
            break;
        case 6:
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    while (choice != 6);
}
