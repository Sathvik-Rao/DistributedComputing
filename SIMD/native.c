#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1300

int main()
{
    // Initialize random number generator
    srand(time(NULL));

    // Allocate memory for matrices A, B, and C
    double *A = (double *)malloc(N * N * sizeof(double));
    double *B = (double *)malloc(N * N * sizeof(double));
    double *C = (double *)malloc(N * N * sizeof(double));

    // Initialize matrices A and B with random numbers
    for (int i = 0; i < N * N; i++)
    {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
    }

    // Multiply matrices A and B and store the result in matrix C
    printf("Multiplying...\n");
    clock_t start_time = clock();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double sum = 0;
            for (int k = 0; k < N; k++)
            {
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
    clock_t end_time = clock();
    printf("Done\n");

    // Print execution time
    double execution_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Execution time(Not-Optimized): %f seconds\n", execution_time);

    // Free memory
    free(A);
    free(B);
    free(C);

    return 0;
}
