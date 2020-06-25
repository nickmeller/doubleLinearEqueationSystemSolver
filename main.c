#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <zconf.h>

#define EPS 0.0000000001

size_t number = -1;

void swap(double *a, double *b) {
    double t = *a;
    *a = *b;
    *b = t;
}

double ** read_matrix(char * filename) {
    FILE * in = fopen(filename, "r");
    if (!in) {
        fprintf(stderr, "Could not open file %s", filename);
        exit(EXIT_FAILURE);
    }
    number = 0;
    if (!fscanf(in, "%ld", &number)) {
        fprintf(stderr, "Could not read matrix from file %s", filename);
        exit(EXIT_FAILURE);
    }
    double ** matrix = malloc((number) * sizeof(double*));
    if (!matrix) {
        fprintf(stderr, "Could not allocate memory");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < number; i++) {
        matrix[i] = malloc((number + 1) * sizeof(double));
        if (!matrix[i]) {
            fprintf(stderr, "Could not allocate memory");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number + 1; j++) {
            if(!fscanf(in, "%lf", &matrix[i][j])) {
                fprintf(stderr, "Could not read_matrix numbers from file %s", filename);
                exit(EXIT_FAILURE);
            }
        }
    }
    fclose(in);
    return matrix;
}

void print_matrix(double ** matrix, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size + 1; j++) {
            fprintf(stderr, "%lf ", matrix[i][j]);
        }
        fprintf(stderr, "\n");
    }
}

int gauss (double ** v, double * ans, size_t n) {
    ptrdiff_t * where = malloc((n) * sizeof(ptrdiff_t));
    size_t m = n;
    for (size_t i = 0; i < n; i++) {
        where[i] = -1;
        ans[i] = 0;
    }
    for (size_t col = 0, row = 0; col < m && row < n; ++col) {
        size_t sel = row;
        for (size_t i = row; i < n; i++) {
            if (fabs(v[i][col] > fabs(v[sel][col]))) {
                sel = i;
            }
        }
        if (fabs(v[sel][col] < EPS))
            continue;
        for (size_t i = col; i <= m; i++) {
            double t = v[sel][i];
            v[sel][i] = v[row][i];
            v[row][i] = t;
        }
        where[col] = row;

        for (size_t i = 0; i < n; i++)
            if (i != row) {
                double c = v[i][col] / v[row][col];
                for (size_t j = col; j <= m; j++)
                    v[i][j] -= v[row][j] * c;
            }
        ++row;

    }
//    for (size_t i = 0; i < n; i++) {
//        fprintf(stderr, "%ld ", where[i]);
//    }
//    fprintf(stderr, "\n");
    for (size_t i = 0; i < m; i++)
        if (where[i] != -1)
            ans[i] = v[where[i]][m] / v[where[i]][i];
    for (size_t i = 0; i < n; i++) {
        double sum = 0;
        for (size_t j = 0; j < m; j++) {
            sum += ans[j] * v[i][j];
        }
        if (fabs (sum - v[i][m]) > EPS)
            return 0;
    }

    for (size_t i = 0; i < m; i++) {
        if (where[i] == -1)
            return -1;
    }
    return 1;
}

void write_result(char * filename, int mode, double * ans) {
    FILE * out = fopen(filename, "w");
    if (!out) {
        fprintf(stderr, "Error while opening file %s", filename);
        exit(EXIT_FAILURE);
    }
    if (mode <= 0) {
        fprintf(out, (mode == -1 ? "Many solutions" : "No solutions"));
    } else {
        for (size_t i = 0; i < number; i++) {
            fprintf(out, "%lf ", ans[i]);
        }
    }
    fclose(out);
}



int main(int argc, char ** argv) {
    if (argc != 3) {
        fprintf(stderr ,"Expected two arguments, found %d", argc - 1);
        exit(EXIT_FAILURE);
    }
    double ** matrix = read_matrix(argv[1]);
    //fprintf(stderr, "Reading successful\n");
//    print_matrix(matrix, number);
    double * ans = malloc(number * sizeof(double));
    int result = gauss(matrix, ans, number);
//    for (size_t i = 0; i < number; i++) {
//        fprintf(stderr, "%lf ", ans[i]);
//    }
    write_result(argv[2], result, ans);
    free(ans);
    for (size_t i = 0; i < number; i++) {
        free(matrix[i]);
    }
    free(matrix);
    exit(EXIT_SUCCESS);
}
