#include <omp.h>
#include <iostream>

void gemm_parallel(int M, int N, int K, double alpha, double* A, double* B, double beta, double* C) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < K; ++k) {
                sum += A[i * K + k] * B[k * N + j];
            }
            C[i * N + j] = alpha * sum + beta * C[i * N + j];
        }
    }
}

int main() {
    int M = 4, N = 4, K = 4;
    double alpha = 1.0, beta = 1.0;
    double A[M * K] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double B[K * N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double C[M * N] = {0};

    gemm_parallel(M, N, K, alpha, A, B, beta, C);

    for (int i = 0; i < M * N; ++i) {
        if (i % N == 0) std::cout << '\n';
        std::cout << C[i] << ' ';
    }
    return 0;
}

