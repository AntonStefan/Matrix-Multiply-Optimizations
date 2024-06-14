/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

/* 
 * Functia aloca matricele necesare, verificand daca au avut loc erori.
 */
void allocate_matrices(int N, double **C, double **temp1, double **temp2, double **temp3) {
    *C = malloc(N * N * sizeof(**C));
    if (NULL == *C) exit(EXIT_FAILURE);

    *temp1 = calloc(N * N, sizeof(**temp1));
    if (NULL == *temp1) exit(EXIT_FAILURE);

    *temp2 = calloc(N * N, sizeof(**temp2));
    if (NULL == *temp2) exit(EXIT_FAILURE);

    *temp3 = calloc(N * N, sizeof(**temp3));
    if (NULL == *temp3) exit(EXIT_FAILURE);
}


/*
 * Implementarea neoptimizată a formulei (At * B + B * A) * Bt
 */
double* my_solver(int N, double *A, double* B) {
    printf("NEOPT SOLVER\n");

    double *C, *temp1, *temp2, *temp3;
    double *At = malloc(N * N * sizeof(double));
    double *Bt = malloc(N * N * sizeof(double));
    
    if (!At || !Bt) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    allocate_matrices(N, &C, &temp1, &temp2, &temp3);

    // Calcularea transpuselor At și Bt
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            At[i * N + j] = A[j * N + i];
            Bt[i * N + j] = B[j * N + i];
        }
    }

    // Calcularea temp1 = At * B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp1[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                temp1[i * N + j] += At[i * N + k] * B[k * N + j];
            }
        }
    }

    // Calcularea temp2 = B * A, ținând cont că A este triunghiular superior
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp2[i * N + j] = 0;
            for (int k = 0; k <= j; k++) {
                temp2[i * N + j] += B[i * N + k] * A[k * N + j];
            }
        }
    }

    // Adunarea temp1 + temp2 și stocarea în temp3
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp3[i * N + j] = temp1[i * N + j] + temp2[i * N + j];
        }
    }

    // Calcularea C = temp3 * Bt
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i * N + j] = 0;
            for (int k = 0; k < N; k++) {
                C[i * N + j] += temp3[i * N + k] * Bt[k * N + j];
            }
        }
    }

    // Eliberarea memoriei alocate
    free(At);
    free(Bt);
    free(temp1);
    free(temp2);
    free(temp3);

    return C;
}
