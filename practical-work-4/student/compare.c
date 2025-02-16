/*
===============================================================================
File:                   compare.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      08.05.2024
Version:                1.0
Description:            This is the file in which the program to compare two BMP
                        images and compute the difference is implemented.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

/**
 * @brief Compares two BMP images and generates a difference image.
 *
 * This function compares two BMP images pixel by pixel. If the pixels at the same position in both images are the same,
 * the corresponding pixel in the result image is the same as the original. If they are different, the corresponding pixel
 * in the result image is red.
 *
 * The images must have the same dimensions and the same number of pixels.
 *
 * @param data1 A pointer to the Pixel array of the first image.
 * @param data2 A pointer to the Pixel array of the second image.
 * @param header A pointer to the BMPHeader structure that contains the image metadata.
 * @return A pointer to the Pixel array of the result image.
 */
Pixel *compare_bmp(Pixel *data1, Pixel *data2, BMPHeader *header);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <file1> <file2> <output>\n", argv[0]);
        goto cleanup;
    }

    FILE *file1 = fopen(argv[1], "rb");
    FILE *file2 = fopen(argv[2], "rb");
    FILE *output = fopen(argv[3], "wb");

    // verify that the files are open
    if (!file1 || !file2 || !output) {
        fprintf(stderr, "Error opening files.\n");
        goto cleanup;
    }

    BMPHeader header1, header2;
    read_bmp_header(file1, &header1);
    read_bmp_header(file2, &header2);

    // verify that the files are BMP files
    if (header1.magic != 0x4D42 || header2.magic != 0x4D42) {
        fprintf(stderr, "Error: files are not BMP files.\n");
        goto cleanup;
    }

    // verify that the files have the same dimensions
    if (header1.width != header2.width || header1.height != header2.height) {
        fprintf(stderr, "Error: images have different dimensions.\n");
        goto cleanup;
    }

    Pixel *data1 = malloc(header1.width * header1.height * sizeof(Pixel));
    if (!data1) {
        fprintf(stderr, "Error allocating memory.\n");
        goto cleanup;
    }

    Pixel *data2 = malloc(header2.width * header2.height * sizeof(Pixel));
    if (!data2) {
        fprintf(stderr, "Error allocating memory.\n");
        goto cleanup;
    }

    Pixel *diff = malloc(header1.width * header1.height * sizeof(Pixel));
    if (!diff) {
        fprintf(stderr, "Error allocating memory.\n");
        goto cleanup;
    }

    // compare the two images
    read_bmp_data(file1, &header1, data1);
    read_bmp_data(file2, &header2, data2);
    diff = compare_bmp(data1, data2, &header1);

    // write the difference to the output file
    write_bmp_header(output, &header1);
    write_bmp_data(output, &header1, diff);

    fclose(file1);
    fclose(file2);
    fclose(output);
    free(data1);
    free(data2);
    free(diff);

    return EXIT_SUCCESS;

cleanup:
    if (file1) fclose(file1);
    if (file2) fclose(file2);
    if (output) fclose(output);
    free(data1);
    free(data2);
    free(diff);

    return EXIT_FAILURE;
}

Pixel *compare_bmp(Pixel *data1, Pixel *data2, BMPHeader *header) {
    int numPixels = header->imageSize / sizeof(Pixel);
    Pixel *result = malloc(header->imageSize);

    if (result == NULL) {
        fprintf(stderr, "Failed to allocate memory for the result image\n");
        goto cleanup;
    }

    for (int i = 0; i < numPixels; i++) {
        if (data1[i].blue != data2[i].blue || data1[i].green != data2[i].green || data1[i].red != data2[i].red) {
            // If the pixels are not the same, set the result pixel to red
            result[i].blue = 0;
            result[i].green = 0;
            result[i].red = 255;
        } else {
            // If the pixels are the same, copy the pixel from data1
            result[i] = data1[i];
        }
    }

    return result;

cleanup:
    free(result);
    return NULL;
}
