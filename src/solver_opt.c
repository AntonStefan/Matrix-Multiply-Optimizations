/*
 * Tema 2 ASC
 * 2024 Spring
 */
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
 * Functia aloca matricele necesare, verificand daca au avut loc erori.
 */
void allocate_matrices(int N, double **C, double **At, double **Bt, double **temp1, double **temp2) {
    register int size = N * N * sizeof(**C);

    *C = malloc(size);
    if (NULL == *C) exit(EXIT_FAILURE);

    *At = malloc(size);
    if (NULL == *At) exit(EXIT_FAILURE);

    *Bt = malloc(size);
    if (NULL == *Bt) exit(EXIT_FAILURE);

    *temp1 = calloc(size, sizeof(**temp1));
    if (NULL == *temp1) exit(EXIT_FAILURE);

    *temp2 = calloc(size, sizeof(**temp2));
    if (NULL == *temp2) exit(EXIT_FAILURE);
}


/*
 * Implementarea optimizată a formulei (At * B + B * A) * Bt
 */
double* my_solver(int N, double *A, double* B) {
    printf("OPT SOLVER\n");

    double *C, *At, *Bt, *temp1, *temp2;
    
    allocate_matrices(N, &C, &At, &Bt, &temp1, &temp2);

    // Calcularea transpuselor At și Bt
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            At[i * N + j] = A[j * N + i];
            Bt[i * N + j] = B[j * N + i];
        }
    }


	
    // Calcularea temp1 = At * B
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            register double sum = 0.0;
            for (register int k = 0; k < N; k++) {
                sum += At[i * N + k] * B[k * N + j];
            }
            temp1[i * N + j] = sum;
        }
    }
	


    // Calcularea temp2 = B * A, ținând cont că A este triunghiular superior ( k <= j )
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            register double sum = 0.0;
            for (register int k = 0; k <= j; k++) {
                sum += B[i * N + k] * A[k * N + j];
            }
            temp2[i * N + j] = sum;
        }
    }

    // Adunarea temp1 + temp2 și stocarea în C
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
            C[i * N + j] = temp1[i * N + j] + temp2[i * N + j];
        }
    }


    // Calcularea C = C * Bt
    for (register int i = 0; i < N; i++) {
        for (register int j = 0; j < N; j++) {
			register double sum = 0.0;
				for (register int k = 0; k < N; k++) {
					sum += C[i * N + k] * Bt[k * N + j];
				}
			temp1[i * N + j] = sum;
		}
	}
	
	// Copiem rezultatul final în C
	for (register int i = 0; i < N; i++) {
		for (register int j = 0; j < N; j++) {
			C[i * N + j] = temp1[i * N + j];
		}
	}
	

	// Eliberarea memoriei alocate
	free(At);
	free(Bt);
	free(temp1);
	free(temp2);

	return C;
}
