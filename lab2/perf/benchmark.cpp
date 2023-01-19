#include <benchmark/benchmark.h>
#include <cstdint>

#include "../src/utils.hpp"
#include "../src/bfs.hpp"

const auto qubic500 = generate_qubic_graph(500);
std::vector<int32_t> distance(500 * 500 * 500, -1);

static void qubic500_benchmark_seq(benchmark::State& state) {
    std::vector<int32_t> distance(qubic500.size(), -1);
    for (auto _ : state) {
        state.PauseTiming();
        for (auto& elem : distance) {
            elem = -1;
        }
        state.ResumeTiming();
        seq_bfs(0, distance, qubic500);
    } 
}
static void qubic500_benchmark_par(benchmark::State& state) {
    for (auto _ : state) {
        state.PauseTiming();
        for (size_t i = 0; i < distance.size(); ++i) {
            distance[i] = -1;
        }
        state.ResumeTiming();
        par_bfs(0, distance, qubic500);
    } 
}

BENCHMARK(qubic500_benchmark_seq)->Iterations(1)->Unit(benchmark::kSecond)->UseRealTime();
BENCHMARK(qubic500_benchmark_par)->Iterations(1)->Unit(benchmark::kSecond)->UseRealTime();

BENCHMARK_MAIN();