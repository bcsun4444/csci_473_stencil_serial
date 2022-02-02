/*
 * FILE: stencil-2d.c
 * AUTHOR: Sean Tronsen
 * PURPOSE: Performs the stenciling operation on the data over a series of specified iterations
 * DATE: 02012022
 */




#include "utilities.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void validate(int argc, char **argv);

void perform_9_point_stenciling(double **matrix_01, double **matrix_02, int rows, int cols);

int main(int argc, char **argv) {

    validate(argc, argv);
    int num_iterations = atoi(argv[1]);
    int rows, cols;
    rows = cols = 0;
    char *initial_data_file_name = argv[2],
            *final_data_file_name = argv[3],
            *all_iterations_data_file_name = argv[4];

    // setup
    double **matrix_01 = read_double_matrix_from_file(initial_data_file_name, &rows, &cols);
    double **matrix_02 = allocate_double_matrix(rows, cols);
    populate_double_matrix(matrix_02, rows, cols);
    write_double_matrix_to_raw_file(matrix_01, rows, cols, all_iterations_data_file_name);


    // iterate
    for (int iter_no = 0; iter_no < num_iterations; iter_no++) {
        perform_9_point_stenciling(matrix_01, matrix_02, rows, cols);
        append_double_matrix_to_raw_file(matrix_02, rows, cols, all_iterations_data_file_name);
        double **temp_pointer = matrix_01;
        matrix_01 = matrix_02;
        matrix_02 = temp_pointer;
        print_double_matrix(matrix_01, rows, cols);
    }

    write_double_matrix_to_file(matrix_01, rows, cols, final_data_file_name);
    deallocate_double_matrix(matrix_01, cols);
    printf("main: Execution complete.");
    exit(EXIT_SUCCESS);
}


void perform_9_point_stenciling(double **matrix_01, double **matrix_02, int rows, int cols) {

    printf("perform_9_point_stenciling: running stencil\n");
    for (int i = 1; i < (cols - 1); i++) {
        for (int j = 1; j < (rows - 1); j++) {
            matrix_02[i][j] = ((
                                       matrix_01[i - 1][j - 1] + matrix_01[i - 1][j] + matrix_01[i - 1][j + 1] +
                                       matrix_01[i][j + 1] + matrix_01[i + 1][j + 1] + matrix_01[i + 1][j] +
                                       matrix_01[i + 1][j - 1] + matrix_01[i][j - 1] + matrix_01[i][j]
                               ) / 9.0);
        }
    }
}


void validate(int argc, char **argv) {
    if (argc != 5) {

        printf("%s \n", argv[0]);
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *initial_data_file_name = argv[2], *final_data_file_name = argv[3], *overall_raw_file_name = argv[4];
    if (strlen(initial_data_file_name) < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided input initial data filename must be at least one character(s) long. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strlen(final_data_file_name) < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided input final data filename must be at least one character(s) long. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (strlen(overall_raw_file_name) < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided input all iterations data filename must be at least one character(s) long. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (strcmp(initial_data_file_name, final_data_file_name) == 0) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The initial and final data files cannot have the same name. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (strcmp(initial_data_file_name, overall_raw_file_name) == 0) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The initial and all iterations data files cannot have the same name. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if (strcmp(final_data_file_name, overall_raw_file_name) == 0) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The final and all iterations data files cannot have the same name. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    int num_iterations = 0;
    num_iterations = atoi(argv[1]);
    if (num_iterations < 1) {
        printf("%s \n", argv[0]);
        perror("Validation Error: The provided iterations argument must be an integer value > 0. \n");
        printf("usage:\t%s <number_of_iterations> <input_file> <output_file> <all_iterations>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("validate: Validation operations completed successfully\n");


}
