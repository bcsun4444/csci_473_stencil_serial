/*
 * FILE     : make-2d.c
 * AUTHOR   : Sean Tronsen
 * DATE     : 02012022
 * PURPOSE  : Makes the initial conditions and boundary values for the matrix
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

void validate(int argc, char **argv);

int main(int argc, char **argv) {
    validate(argc, argv);
    int rows, cols;
    char *file_name;
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    file_name = argv[3];

    // begin setup
    double **matrix = allocate_double_matrix(rows, cols);
    populate_double_matrix(matrix, rows, cols);

    // write to file
    write_double_matrix_to_file(matrix, rows, cols, file_name);

    // deallocate and exit
    deallocate_double_matrix(matrix, cols);
    exit(EXIT_SUCCESS);
}


void validate(int argc, char **argv) {
    if (argc != 4) {
        printf("%s \n", argv[0]);
        printf("usage:\t%s <rows_as_int> <cols_as_int> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int rows, cols;
    char *file_name;
    rows = cols = 0;
    rows = atoi(argv[1]);
    cols = atoi(argv[2]);
    if (rows <= 3 || cols <= 3) {
        printf("%s \n", argv[0]);
        perror("Validation Error: Integer values are required for the row and column program arguments. Additionally, the values entered must be <= 3\n");
        printf("usage:\t%s <rows_as_int> <cols_as_int> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    file_name = argv[3];
    if (strlen(file_name) < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided filename must be at least one character(s) long. \n");
        printf("usage:\t%s <rows_as_int> <cols_as_int> <output_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}



