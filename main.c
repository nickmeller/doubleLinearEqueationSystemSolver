#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t number = -1;

double ** read(char * filename) {
    FILE * in = fopen(filename, "r");
    if (!in) {
        fprintf(stderr, "Could not open file %s", filename);
        exit(EXIT_FAILURE);
    }
    number = 0;
    if (!fscanf(in, "%ld", &number)) {
        fprintf(stderr, "Could not read from file %s", filename);
        exit(EXIT_FAILURE);
    }
    double ** matrix = malloc((number + 1) * (number + 1) * sizeof(double*));
    if (!matrix) {
        fprintf(stderr, "Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < number + 1; i++) {
        matrix[i] = malloc((number + 1) * sizeof(double));
        if (!matrix[i]) {
            fprintf(stderr, "Could not allocate memory");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < number + 1; i++) {
        for (int j = 0; j < number + 1; j++) {
            if(!fscanf(in, "%lf", &matrix[j][i])) {
                fprintf(stderr, "Could not read numbers from file %s", filename);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(in);
    return matrix;
}

void print_matrix(double ** matrix, int transpose, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            fprintf(stderr, "%lf ", (transpose? matrix[i][j] : matrix[j][i]));
        }
        fprintf(stderr, "\n");
    }
}

int gauss (double ** v, double * ans, size_t n) {
    int * where = malloc((n - 1) * sizeof(int));
    memset(where, -1, n -1);
    for (int i = 0, j = 0)
}



int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr ,"Expected two arguments, found %d", argc - 1);
        exit(EXIT_FAILURE);
    }
    double ** matrix = read(argv[1]);
    fprintf(stderr, "Reading successful\n");
    //print_matrix(matrix, 0, number);


    return 0;
}
