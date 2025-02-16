/*
===============================================================================
File:                   bmp.c
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      08.05.2024
Version:                1.0
Description:            This is the file in which the utils functions for the BMP
                        file format are implemented.
===============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

void read_bmp_header(FILE *file, BMPHeader *header) {
    fread(&header->magic, sizeof(header->magic), 1, file);
    fread(&header->fileSize, sizeof(header->fileSize), 1, file);
    fread(&header->reserved1, sizeof(header->reserved1), 1, file);
    fread(&header->reserved2, sizeof(header->reserved2), 1, file);
    fread(&header->dataOffset, sizeof(header->dataOffset), 1, file);
    fread(&header->headerSize, sizeof(header->headerSize), 1, file);
    fread(&header->width, sizeof(header->width), 1, file);
    fread(&header->height, sizeof(header->height), 1, file);
    fread(&header->planes, sizeof(header->planes), 1, file);
    fread(&header->bpp, sizeof(header->bpp), 1, file);
    fread(&header->compression, sizeof(header->compression), 1, file);
    fread(&header->imageSize, sizeof(header->imageSize), 1, file);
    fread(&header->xResolution, sizeof(header->xResolution), 1, file);
    fread(&header->yResolution, sizeof(header->yResolution), 1, file);
    fread(&header->colorsUsed, sizeof(header->colorsUsed), 1, file);
    fread(&header->importantColors, sizeof(header->importantColors), 1, file);
}

void write_bmp_header(FILE *file, BMPHeader *header) {
    fwrite(&header->magic, sizeof(header->magic), 1, file);
    fwrite(&header->fileSize, sizeof(header->fileSize), 1, file);
    fwrite(&header->reserved1, sizeof(header->reserved1), 1, file);
    fwrite(&header->reserved2, sizeof(header->reserved2), 1, file);
    fwrite(&header->dataOffset, sizeof(header->dataOffset), 1, file);
    fwrite(&header->headerSize, sizeof(header->headerSize), 1, file);
    fwrite(&header->width, sizeof(header->width), 1, file);
    fwrite(&header->height, sizeof(header->height), 1, file);
    fwrite(&header->planes, sizeof(header->planes), 1, file);
    fwrite(&header->bpp, sizeof(header->bpp), 1, file);
    fwrite(&header->compression, sizeof(header->compression), 1, file);
    fwrite(&header->imageSize, sizeof(header->imageSize), 1, file);
    fwrite(&header->xResolution, sizeof(header->xResolution), 1, file);
    fwrite(&header->yResolution, sizeof(header->yResolution), 1, file);
    fwrite(&header->colorsUsed, sizeof(header->colorsUsed), 1, file);
    fwrite(&header->importantColors, sizeof(header->importantColors), 1, file);
}

void read_bmp_data(FILE *file, BMPHeader *header, Pixel *data) {
    // Calculate the padding for each row
    int padding = (4 - (header->width * sizeof(Pixel)) % 4) % 4;

    if (fseek(file, header->dataOffset, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking to data offset in the BMP file\n");
        goto error;
    }

    for (int i = 0; i < header->height; i++) {
        // BMP stores the rows in reverse order, so we adjust the position accordingly
        if (fread(&data[(header->height - i - 1) * header->width], sizeof(Pixel), header->width, file) != header->width) {
            fprintf(stderr, "Error reading pixel data from the BMP file\n");
            goto error;
        }

        // Skip the padding
        if (fseek(file, padding, SEEK_CUR) != 0) {
            fprintf(stderr, "Error seeking over padding in the BMP file\n");
            goto error;
        }
    }

    return;

error:
    return;
}

void write_bmp_data(FILE *file, BMPHeader *header, Pixel *data) {
    // Calculate the padding for each row
    int padding = (4 - (header->width * sizeof(Pixel)) % 4) % 4;

    if (fseek(file, header->dataOffset, SEEK_SET) != 0) {
        fprintf(stderr, "Error seeking to data offset in the BMP file\n");
        goto error;
    }

    fseek(file, header->dataOffset, SEEK_SET);

    for (int i = 0; i < header->height; i++) {
        // BMP stores the rows in reverse order, so we adjust the position accordingly
        if (fwrite(&data[(header->height - i - 1) * header->width], sizeof(Pixel), header->width, file) != header->width) {
            fprintf(stderr, "Error writing pixel data to the BMP file\n");
            goto error;
        }

        // Write the padding
        for (int j = 0; j < padding; j++) {
            if (fputc(0, file) == EOF) {
                fprintf(stderr, "Error writing padding to the BMP file\n");
                goto error;
            }
            fputc(0, file);
        }
    }

    return;

error:
    return;
}
