/*
===============================================================================
File:                   gray.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      08.05.2024
Version:                1.0
Description:            This is the file in which the program to convert a BMP
                        image to black and white is implemented.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

void convert_to_gray(BMPHeader header, Pixel *data);


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
        fprintf(stderr, "Error opening file.\n");
        goto cleanup;
    }

    output = fopen(argv[2], "wb");
    if (!output) {
        fprintf(stderr, "Error opening file.\n");
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

    // convert the image to black and white
    convert_to_gray(header, data);

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
    free(data);

    return EXIT_FAILURE;
}

void convert_to_gray(BMPHeader header, Pixel *data) {
    for (int i = 0; i < header.width * header.height; i++) {
        uint8_t gray = (data[i].red + data[i].green + data[i].blue) / 3;
        data[i].red = gray;
        data[i].green = gray;
        data[i].blue = gray;
    }
}
