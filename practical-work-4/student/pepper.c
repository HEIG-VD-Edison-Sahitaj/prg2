/*
===============================================================================
File:                   pepper.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      08.05.2024
Version:                1.0
Description:            This is the file in which the program to remove salt-and-pepper
                        noise from a BMP image is implemented.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

/**
 * @brief Sorts an array of unsigned char using the bubble sort algorithm.
 *
 * This function sorts an array of unsigned char in ascending order using the bubble sort algorithm.
 * Bubble sort is a simple sorting algorithm that repeatedly steps through the list, compares adjacent elements and swaps them if they are in the wrong order.
 * The pass through the list is repeated until the list is sorted.
 *
 * @param arr A pointer to the unsigned char array to sort.
 * @param n The number of elements in the array.
 */
void bubble_sort(unsigned char *arr, int n);

/**
 * @brief Applies a median filter to a BMP image.
 *
 * This function applies a median filter to a BMP image. The median filter is a non-linear digital filtering technique,
 * often used to remove noise from an image or signal. The main idea of the median filter is to run through the signal
 * entry by entry, replacing each entry with the median of neighboring entries.
 *
 * @param data A pointer to the Pixel array of the image.
 * @param header A pointer to the BMPHeader structure that contains the image metadata.
 */
void apply_median_filter(Pixel *data, BMPHeader *header);

int main(int argc, char *argv[]) {
    FILE *input = NULL;
    FILE *output = NULL;
    Pixel *data = NULL;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input> <output>\n", argv[0]);
        goto cleanup;
    }

    input = fopen(argv[1], "rb");
    if (!input) {
        fprintf(stderr, "Error: could not open input file.\n");
        goto cleanup;
    }

    output = fopen(argv[2], "wb");
    if (!output) {
        fprintf(stderr, "Error: could not open output file.\n");
        goto cleanup;
    }

    BMPHeader header;
    read_bmp_header(input, &header);

    // verify that the file is a BMP file
    if (header.magic != 0x4D42) {
        fprintf(stderr, "Error: file %s is not a BMP file.\n", argv[1]);
        goto cleanup;
    }

    data = malloc(header.width * header.height * sizeof(Pixel));
    if (!data) {
        fprintf(stderr, "Error: could not allocate memory for image data.\n");
        goto cleanup;
    }

    // read the image data
    read_bmp_data(input, &header, data);

    // apply the median filter
    apply_median_filter(data, &header);

    // write the new image data
    write_bmp_header(output, &header);
    write_bmp_data(output, &header, data);

    fclose(input);
    fclose(output);
    free(data);

    return EXIT_SUCCESS;

cleanup:
    if (input) fclose(input);
    if (output) fclose(output);
    if (data) free(data);

    return EXIT_FAILURE;
}

void bubble_sort(unsigned char *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                unsigned char temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void apply_median_filter(Pixel *data, BMPHeader *header) {
    // Allocate memory for a copy of the image
    Pixel *copy = malloc(header->width * header->height * sizeof(Pixel));

    if (copy == NULL) {
        fprintf(stderr, "Error: could not allocate memory for image copy.\n");
        return;
    }

    memcpy(copy, data, header->width * header->height * sizeof(Pixel));

    // Loop over each pixel in the image (excluding the border)
    for (int i = 1; i < header->height - 1; i++) {
        for (int j = 1; j < header->width - 1; j++) {
            unsigned char neighbors[9];
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    neighbors[(di + 1) * 3 + (dj + 1)] = copy[(i + di) * header->width + (j + dj)].red;
                }
            }

            // Sort the red values and find the median
            bubble_sort(neighbors, 9);
            unsigned char median = neighbors[4];

            // Set the red, green, and blue values of the pixel to the median
            data[i * header->width + j].red = median;
            data[i * header->width + j].green = median;
            data[i * header->width + j].blue = median;
        }
    }

    free(copy);
    return;
}
