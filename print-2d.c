/*
 * FILE: print-2d.c
 * AUTHOR: Sean Tronsen
 * PURPOSE: prints out the matrix stored with the data file
 * DATE: 02012022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

void validate(int argc, char **argv);
int main(int argc, char **argv) {

    // run validation
    validate(argc, argv);

    // prep
    int rows, cols;
    rows = cols = 0;
    char *file_name = argv[1];
    double **matrix;

    // pull matrix and metadata from file
    matrix = read_double_matrix_from_file(file_name, &rows, &cols);
    print_double_matrix(matrix, rows, cols);

    // deallocate and exit
    deallocate_double_matrix(matrix, rows);
    exit(EXIT_SUCCESS);
}


void validate(int argc, char **argv) {
    if (argc != 2) {
        printf("%s \n", argv[0]);
        printf("usage:\t%s <data_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *file_name = argv[1];
    if (strlen(file_name) < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided filename must be at least one character(s) long. \n");
        printf("usage:\t%s <data_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}
