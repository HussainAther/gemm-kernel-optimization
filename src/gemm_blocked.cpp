#include <iostream>
#include <algorithm>

void gemm_blocked(int M, int N, int K, double alpha, double* A, double* B, double beta, double* C, int blockSize) {
    for (int i0 = 0; i < M; i0 += blockSize) {
        for (int j0 = 0; j < N; j0 += blockSize) {
            for (int k0 = 0; k < K; k0 += blockSize) {
                for (int i = i0; i < std::min(i0 + blockSize, M); ++i) {
                    for (int j = j0; j < std::min(j0 + blockSize, N); ++j) {
                        double sum = 0.0;
                        for (int k = k0; k < std::min(k0 + blockSize, K); ++k) {
                            sum += A[i * K + k] * B[k * N + j];
                        }
                        C[i * N + j] = alpha * sum + beta * C[i * N + j];
                    }
                }
            }
        }
    }
}

int main() {
    int M = 4, N = 4, K = 4, blockSize = 2;
    double alpha = 1.0, beta = 1.0;
    double A[M * K] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double B[K * N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double C[M * N] = {0};

    gemm_blocked(M, N, K, alpha, A, B, beta, C, blockSize);

    for (int i = 0; i < M * N; ++i) {
        if (i % N == 0) std::cout << '\n';
        std::cout << C[i] << ' ';
    }
    return 0;
}

