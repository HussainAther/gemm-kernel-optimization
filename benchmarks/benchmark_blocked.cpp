#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

void gemm_blocked(int M, int N, int K, double alpha, double* A, double* B, double beta, double* C, int blockSize) {
    for (int i0 = 0; i0 < M; i0 += blockSize) {
        for (int j0 = 0; j0 < N; j0 += blockSize) {
            for (int k0 = 0; k0 < K; k0 += blockSize) {
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
    const int M = 512, N = 512, K = 512; // Matrix dimensions
    const int blockSize = 64; // Block size for blocking optimization
    const double alpha = 1.0, beta = 0.0;

    // Initialize matrices A, B, and C
    std::vector<double> A(M * K, 1.0);
    std::vector<double> B(K * N, 1.0);
    std::vector<double> C(M * N, 0.0);

    auto start = std::chrono::high_resolution_clock::now();
    gemm_blocked(M, N, K, alpha, A.data(), B.data(), beta, C.data(), blockSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double gflops = (2.0 * M * N * K) / (duration.count() * 1

