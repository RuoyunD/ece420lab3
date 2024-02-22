#include "Lab3IO.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void swapRows(double **G, int row1, int row2) {
    double* temp = G[row1];
    G[row1] = G[row2];
    G[row2] = temp;
}

void gaussianElimination(double **G, int n) {
    for (int k = 0; k < n - 1; k++) {
        // Pivoting
        int maxRow = k;
        for (int i = k + 1; i < n; i++)
            // selecting the best row to use as the pivot
            if (fabs(G[i][k]) > fabs(G[maxRow][k]))
                maxRow = i;
        swapRows(G, k, maxRow);

        // Elimination
        for (int i = k + 1; i < n; i++) {
            double factor = G[i][k] / G[k][k];
            for (int j = k; j <= n; j++) // Include n for augmented part
                G[i][j] -= factor * G[k][j];
        }
    }
}

void jordanElimination(double **G, int n) {
    for (int k = n - 1; k > 0; k--) {
        for (int i = 0; i < k; i++) {
            double factor = G[i][k] / G[k][k];
            G[i][n] -= factor * G[k][n]; // Adjusting the augmented column
            G[i][k] = 0; // Setting the upper part to 0
        }
    }
}

// Normalization (Making diagonal elements 1)
void normalize(double **G, int n) {
    for (int i = 0; i < n; i++) {
        double diag = G[i][i];
        for (int j = 0; j <= n; j++) // Include augmented column
            G[i][j] /= diag;
    }
}

int main(int argc, char *argv[]) {
    double **G;
    int size;
    double* x;
    double start, end;
    int i;

    // if (argc != 1) {
    //     printf("Usage: %s <number of thread>\n", argv[0]);
    //     return 1;
    // }

    // Loading the input matrix and vector
    if (Lab3LoadInput(&G, &size)) {
        fprintf(stderr, "Error loading input.\n");
        return 1;
    }

    // Start timing
    GET_TIME(start);

    gaussianElimination(G, size);
    jordanElimination(G, size);
    normalize(G, size);

    // Extract solution vector x
    x = CreateVec(size);
    for (i = 0; i < size; ++i) {
        x[i] = G[i][size];
    }

    // End timing
    GET_TIME(end);

    // Saving the output vector x and the execution time
    double Time = end - start;
    if (Lab3SaveOutput(x, size, Time)) {
        fprintf(stderr, "Error saving output.\n");
        return 1;
    }

    // Freeing allocated memory
    DestroyMat(G, size);
    DestroyVec(x);

    return 0;
}