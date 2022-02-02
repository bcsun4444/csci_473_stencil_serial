/*
 * FILE: utilities.h
 * AUTHOR: Sean Tronsen
 * PURPOSE: header file for the associated source file
 * DATE: 02012022
 */

#ifndef CSCI_473_STENCIL_SERIAL_UTILITIES_H
#define CSCI_473_STENCIL_SERIAL_UTILITIES_H
void print_double_matrix(double** matrix, int rows, int cols);
double **read_double_matrix_from_file(char *file_name, int *rows_reference, int *cols_reference);
void write_double_matrix_to_file(double** matrix, int rows, int cols, char* file_name);
void write_double_matrix_to_raw_file(double **matrix, int rows, int cols, char *file_name);
void append_double_matrix_to_raw_file(double **matrix, int rows, int cols, char *file_name);
double** allocate_double_matrix(int rows, int cols);
void deallocate_double_matrix(double** matrix, int cols);
void populate_double_matrix(double** matrix, int rows, int cols);
#endif //CSCI_473_STENCIL_SERIAL_UTILITIES_H
