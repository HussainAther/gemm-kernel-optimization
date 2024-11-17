# Compiler and flags
CC = g++
CFLAGS = -O3 -Wall -fopenmp -march=native
LDFLAGS = -lm

# Directories
SRC_DIR = src
BENCH_DIR = benchmarks
BUILD_DIR = build

# Source files
NAIVE_SRC = $(SRC_DIR)/gemm_naive.cpp
BLOCKED_SRC = $(SRC_DIR)/gemm_blocked.cpp
SIMD_SRC = $(SRC_DIR)/gemm_simd.cpp
PARALLEL_SRC = $(SRC_DIR)/gemm_parallel.cpp

NAIVE_BENCH = $(BENCH_DIR)/benchmark_naive.cpp
BLOCKED_BENCH = $(BENCH_DIR)/benchmark_blocked.cpp

# Executables
NAIVE_EXEC = $(BUILD_DIR)/gemm_naive
BLOCKED_EXEC = $(BUILD_DIR)/gemm_blocked
SIMD_EXEC = $(BUILD_DIR)/gemm_simd
PARALLEL_EXEC = $(BUILD_DIR)/gemm_parallel

NAIVE_BENCH_EXEC = $(BUILD_DIR)/benchmark_naive
BLOCKED_BENCH_EXEC = $(BUILD_DIR)/benchmark_blocked

# Default target
all: $(NAIVE_EXEC) $(BLOCKED_EXEC) $(SIMD_EXEC) $(PARALLEL_EXEC) $(NAIVE_BENCH_EXEC) $(BLOCKED_BENCH_EXEC)

# Build rules
$(NAIVE_EXEC): $(NAIVE_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(BLOCKED_EXEC): $(BLOCKED_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(SIMD_EXEC): $(SIMD_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(PARALLEL_EXEC): $(PARALLEL_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

$(NAIVE_BENCH_EXEC): $(NAIVE_BENCH) $(NAIVE_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BLOCKED_BENCH_EXEC): $(BLOCKED_BENCH) $(BLOCKED_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Clean up build files
clean:
	rm -rf $(BUILD_DIR)

