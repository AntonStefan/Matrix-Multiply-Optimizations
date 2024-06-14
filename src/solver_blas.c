/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <cblas.h>
#include <stdlib.h>
#include <string.h>

void allocate_matrices(int N, double **C, double **temp1, double **temp2) {
    *C = malloc(N * N * sizeof(**C));
    if (NULL == *C) exit(EXIT_FAILURE);

    *temp1 = malloc(N * N * sizeof(**temp1));
    if (NULL == *temp1) exit(EXIT_FAILURE);

    *temp2 = malloc(N * N * sizeof(**temp2));
    if (NULL == *temp2) exit(EXIT_FAILURE);
}

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
  	double *C, *temp1, *temp2;
    double *At = malloc(N * N * sizeof(double));
    double *Bt = malloc(N * N * sizeof(double));
    
    if (!At || !Bt) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    allocate_matrices(N, &C, &temp1, &temp2);

    // Calcularea transpuselor At și Bt
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            At[i * N + j] = A[j * N + i];
            Bt[i * N + j] = B[j * N + i];
        }
    }

    // temp1 = At * B, tinem cont ca A superior triunghiulara prin CblasUpper
    memcpy(temp1, B, N * N * sizeof(*temp1));

    cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1.0, A, N, temp1, N);

    // temp2 = B * A
    memcpy(temp2, B, N * N * sizeof(*temp2));
    cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1.0, A, N, temp2, N);

    // C = temp1 + temp2 folosind cblas_daxpy
    memcpy(C, temp1, N * N * sizeof(*C));
    cblas_daxpy(N * N, 1.0, temp2, 1, C, 1);

    // C = C * Bt
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N, N, N, 1.0, C, N, Bt, N, 0.0, temp1, N);
    memcpy(C, temp1, N * N * sizeof(*C));

    // Eliberarea memoriei alocate
    free(At);
    free(Bt);
    free(temp1);
    free(temp2);

    return C;
}
