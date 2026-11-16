#include <stdio.h>
#include <time.h>
#include <stdlib.h>

volatile long long sink;

void por_linha(int **A, int N) {
    long long sum = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            sum += A[i][j];
    sink = sum;
}

void por_coluna(int **A, int N) {
    long long sum = 0;
    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++)
            sum += A[i][j];
    sink = sum;
}

double medir(void (*fn)(int**, int), int **A, int N, int reps) {
    clock_t t = clock();
    for (int r = 0; r < reps; r++) fn(A, N);
    return (double)(clock() - t) / CLOCKS_PER_SEC / reps;
}

int main() {
    int tamanhos[] = {512, 1024, 2048, 4096};
    int reps[]     = {200,  50,   10,    3};

    printf("%-6s | %-12s | %-12s | %-8s\n", "N", "Linha (s)", "Coluna (s)", "Razao");
    printf("-------|--------------|--------------|----------\n");

    for (int t = 0; t < 4; t++) {
        int N = tamanhos[t];
        int r = reps[t];

        int **A = malloc(N * sizeof(int*));
        for (int i = 0; i < N; i++) {
            A[i] = malloc(N * sizeof(int));
            for (int j = 0; j < N; j++) A[i][j] = i + j;
        }

        double tl = medir(por_linha,  A, N, r);
        double tc = medir(por_coluna, A, N, r);

        printf("%-6d | %-12.6f | %-12.6f | %-8.2f\n", N, tl, tc, tc/tl);

        for (int i = 0; i < N; i++) free(A[i]);
        free(A);
    }
    return 0;
}