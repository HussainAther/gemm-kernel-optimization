#include <iostream>
#include <vector>
#include <chrono>

void gemm_naive(int M, int N, int K, double alpha, double* A, double* B, double beta, double* C) {
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
    const int M = 512, N = 512, K = 512; // Matrix dimensions
    const double alpha = 1.0, beta = 0.0;

    // Initialize matrices A, B, and C
    std::vector<double> A(M * K, 1.0);
    std::vector<double> B(K * N, 1.0);
    std::vector<double> C(M * N, 0.0);

    auto start = std::chrono::high_resolution_clock::now();
    gemm_naive(M, N, K, alpha, A.data(), B.data(), beta, C.data());
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double gflops = (2.0 * M * N * K) / (duration.count() * 1e9);

    std::cout << "Naive GEMM Execution Time: " << duration.count() << " seconds\n";
    std::cout << "Performance: " << gflops << " GFLOPs\n";

    return 0;
}

