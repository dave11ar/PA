#include <random>
#include <vector>
#include <functional>

#include <benchmark/benchmark.h>

#include "../src/seq/quicksort.hpp"
#include "../src/par/quicksort.hpp"

static void quicksort_benchmark(
    benchmark::State& state, 
    std::function<void(std::vector<uint32_t>&)> fun) {
    for (auto _ : state) {
        state.PauseTiming();
        std::mt19937 gen(1337);
        std::vector<uint32_t> vec(1e8);
        for (size_t i = 0; i < 1e8; ++i) {
            vec[i] = gen();
        }

        state.ResumeTiming();

        fun(vec);
    } 
}

BENCHMARK_CAPTURE(quicksort_benchmark, seq, 
    [](std::vector<uint32_t>& vec){
        seq::quicksort(vec.begin(), vec.end());
    })->Iterations(5)->Unit(benchmark::kMillisecond)->UseRealTime();

BENCHMARK_CAPTURE(quicksort_benchmark, par, 
    [](std::vector<uint32_t>& vec){
        par::quicksort(vec.begin(), vec.end());
    })->Iterations(5)->Unit(benchmark::kMillisecond)->UseRealTime();

BENCHMARK_MAIN();