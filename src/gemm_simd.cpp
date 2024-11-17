#include <immintrin.h>
#include <iostream>

void gemm_simd(int M, int N, int K, double alpha, double* A, double* B, double beta, double* C) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            __m256d sum = _mm256_setzero_pd();
            for (int k = 0; k < K; k += 4) {
                __m256d vecA = _mm256_loadu_pd(&A[i * K + k]);
                __m256d vecB = _mm256_loadu_pd(&B[k * N + j]);
                sum = _mm256_fmadd_pd(vecA, vecB, sum);
            }
            double temp[4];
            _mm256_storeu_pd(temp, sum);
            double total = temp[0] + temp[1] + temp[2] + temp[3];
            C[i * N + j] = alpha * total + beta * C[i * N + j];
        }
    }
}

int main() {
    int M = 4, N = 4, K = 4;
    double alpha = 1.0, beta = 1.0;
    double A[M * K] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double B[K * N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double C[M * N] = {0};

    gemm_simd(M, N, K, alpha, A, B, beta, C);

    for (int i = 0; i < M * N; ++i) {
        if (i % N == 0) std::cout << '\n';
        std::cout << C[i] << ' ';
    }
    return 0;
}

