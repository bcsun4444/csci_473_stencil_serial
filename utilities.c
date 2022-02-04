/*
 * FILE: utilities.c
 * AUTHOR: Sean Tronsen
 * PURPOSE: Contains functions used between multiple application files
 * DATE: 02012022
 */
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"


// DEF: function prints a formatted output of the matrix to the console
void print_double_matrix(double **matrix, int rows, int cols) {
    printf("print_double_matrix: printing matrix\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("print_double_matrix: printing complete\n");
}


// DEF: function reads in a double matrix and metadata from file using the provided args
// NOTE: THIS FUNCTION REQUIRES YOU TO DEALLOCATE THE MEMORY
// USED FOR THE MATRIX OUTSIDE THE SCOPE
double **read_double_matrix_from_file(char *file_name, int *rows_reference, int *cols_reference) {

    // force the reference values to zero
    *rows_reference = *cols_reference = 0;
    FILE *file_handler = fopen(file_name, "r");

    // read metadata
    fread(rows_reference, 1, sizeof(int), file_handler);
    fread(cols_reference, 1, sizeof(int), file_handler);

    // allocate using meta data
    double **matrix = allocate_double_matrix(*rows_reference, *cols_reference);

    // populate using data from file
    for (int row_no = 0; row_no < *rows_reference; row_no++) {
        fread(matrix[row_no], 1, (*cols_reference * sizeof(double)), file_handler);
    }

    // close the file and return the matrix
    fclose(file_handler);
    return matrix;
}

// DEF: function takes in specified arguments and writes the provided matrix to a file
void write_double_matrix_to_file(double **matrix, int rows, int cols, char *file_name) {
    FILE *out_file_handler = fopen(file_name, "w");
    fwrite(&rows, 1, sizeof(int), out_file_handler);
    fwrite(&cols, 1, sizeof(int), out_file_handler);
    for (int row_no = 0; row_no < rows; row_no++) {
        fwrite(matrix[row_no], 1, (cols * sizeof(double)), out_file_handler);
    }
    fclose(out_file_handler);
    printf("write_double_matrix_to_file: data was successfully written to %s\n", file_name);
}


// DEF: function takes in specified arguments and writes the provided matrix to a raw file
void write_double_matrix_to_raw_file(double **matrix, int rows, int cols, char *file_name) {
    FILE *out_file_handler = fopen(file_name, "w");
    for (int row_no = 0; row_no < rows; row_no++) {
        fwrite(matrix[row_no], 1, (cols * sizeof(double)), out_file_handler);
    }
    fclose(out_file_handler);
    printf("write_double_matrix_to_file: data was successfully written to %s\n", file_name);
}


// DEF: function takes in specified arguments and appends the provided matrix to a raw file
void append_double_matrix_to_raw_file(double **matrix, int rows, int cols, char *file_name) {
    FILE *out_file_handler = fopen(file_name, "a");
    for (int row_no = 0; row_no < rows; row_no++) {
        fwrite(matrix[row_no], 1, (cols * sizeof(double)), out_file_handler);
    }
    fclose(out_file_handler);
    printf("write_double_matrix_to_file: data was successfully written to %s\n", file_name);
}


// DEF: function allocates a double matrix of the specified size using the provided args
double **allocate_double_matrix(int rows, int cols) {
    double **matrix = (double **) malloc(rows * (sizeof(double *)));
    for (int row_no = 0; row_no < rows; row_no++) {
        matrix[row_no] = (double *) malloc(cols * sizeof(double));
    }
    return matrix;
}

// DEF: function deallocates a double matrix using the provided args
void deallocate_double_matrix(double **matrix, int rows) {
    for (int row_no = 0; row_no < rows; row_no++) {
        free(matrix[row_no]);
    }
    free(matrix);
}

// DEF: function sets the provided double matrix up with initial data for stenciling
void populate_double_matrix(double **matrix, int rows, int cols) {

    for (int row_no = 0; row_no < rows; row_no++) {
        double *current_arr = matrix[row_no];
        current_arr[0] = current_arr[cols - 1] = 1.0;
        for (int col_no = 1; col_no < (cols - 1); col_no++) {
            current_arr[col_no] = 0.0;
        }
    }
}



