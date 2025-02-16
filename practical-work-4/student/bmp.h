/*
===============================================================================
File:                   bmp.h
Course:                 PRG2
Year:                   2024
Author:                 Basile Cuneo
Creation Date:          25.04.2024
Modification Author:    Edison Sahitaj, Victor Nicolet
Modification Date:      08.05.2024
Version:                1.0
Description:            This is the file in which the utils functions for the BMP
                        file format are declared, as well as the structures used.
===============================================================================
*/

#ifndef BMP_H
#define BMP_H

#include <stdint.h>

/**
 * @brief A structure representing a BMP file header.
 *
 * This structure represents a BMP file header. It contains metadata about the image, such as its dimensions,
 * the number of colors used, the resolution, and more.
 */
typedef struct {
    uint16_t magic; // Nombre MAGIC
    uint32_t fileSize; // Taille totale du fichier
    uint16_t reserved1; // Réservé (0)
    uint16_t reserved2; // Réservé (0)
    uint32_t dataOffset; // Offset des données de l'image
    uint32_t headerSize; // Taille de l'en-tête du fichier
    int32_t width; // Largeur de l'image
    int32_t height; // Hauteur de l'image
    uint16_t planes; // Nombre de plans (toujours 1)
    uint16_t bpp; // Bits par pixel (24 bits dans notre cas)
    uint32_t compression; // Méthode de compression (0 pour non compressé)
    uint32_t imageSize; // Taille de l'image (sans en-tête)
    int32_t xResolution; // Résolution horizontale (en pixels par mètre)
    int32_t yResolution; // Résolution verticale (en pixels par mètre)
    uint32_t colorsUsed; // Nombre de couleurs utilisées dans l'image (0 pour toutes)
    uint32_t importantColors; // Nombre de couleurs importantes (0 pour toutes)
} BMPHeader;

/**
 * @brief A structure representing a pixel in a BMP image.
 *
 * This structure represents a pixel in a BMP image. It contains the blue, green, and red color components of the pixel.
 * Each color component is an 8-bit unsigned integer, which means it can take a value between 0 and 255.
 */
typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} Pixel;

/**
 * @brief Reads the BMP file header from a file.
 *
 * This function reads the BMP file header from the given file and stores the information in a BMPHeader structure.
 * The file must be open for reading and positioned at the start of the BMP file header.
 *
 * @param file A pointer to the file to read from.
 * @param header A pointer to the BMPHeader structure to fill.
 */
void read_bmp_header(FILE *file, BMPHeader *header);

/**
 * @brief Writes the BMP file header to a file.
 *
 * This function writes the BMP file header to the given file from a BMPHeader structure.
 * The file must be open for writing.
 *
 * @param file A pointer to the file to write to.
 * @param header A pointer to the BMPHeader structure to read from.
 */
void write_bmp_header(FILE *file, BMPHeader *header);

/**
 * @brief Reads the BMP image data from a file.
 *
 * This function reads the BMP image data from the given file and stores the pixel information in a Pixel array.
 * The file must be open for reading and the header must be correctly filled.
 * The data array must be large enough to hold all the pixels (width * height).
 *
 * @param file A pointer to the file to read from.
 * @param header A pointer to the BMPHeader structure that contains the image metadata.
 * @param data A pointer to the Pixel array to fill with the image data.
 */
void read_bmp_data(FILE *file, BMPHeader *header, Pixel *data);

/**
 * @brief Writes the BMP image data to a file.
 *
 * This function writes the BMP image data to the given file from a Pixel array.
 * The file must be open for writing and the header must be correctly filled.
 * The data array must contain enough pixels for the image (width * height).
 *
 * @param file A pointer to the file to write to.
 * @param header A pointer to the BMPHeader structure that contains the image metadata.
 * @param data A pointer to the Pixel array that contains the image data.
 */
void write_bmp_data(FILE *file, BMPHeader *header, Pixel *data);

#endif // BMP_H
