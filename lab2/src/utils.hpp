#pragma once

#include <cstdint>
#include <vector>
#include <functional>
#include <iostream>
inline int32_t calc_index(int32_t n, int32_t i, int32_t j, int32_t k) {
    return i * n * n + j * n + k;
}

inline bool check_correctness(int32_t n, int32_t v, int8_t v_) {
    int32_t a = v + v_;
    return (0 <= a) && (a < n);
}

inline void try_add(
    int32_t n, std::vector<int32_t>& edges, 
    int32_t i, int32_t j, int32_t k, 
    int8_t i_, int8_t j_, int8_t k_) {
    if (check_correctness(n, i, i_) &&
        check_correctness(n, j, j_) &&
        check_correctness(n, k, k_)) {
        edges.push_back(calc_index(n, i + i_, j + j_, k + k_));
    }
}

inline std::vector<std::vector<int32_t>> generate_qubic_graph(int32_t n) {
    std::vector<std::vector<int32_t>> graph(n * n * n);

    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < n; ++j) {
            for (int32_t k = 0; k < n; ++k) {
                const auto try_add_b = [n, i, j, k, &graph](int8_t i_, int8_t j_, int8_t k_) {
                    try_add(n, graph[calc_index(n, i, j, k)], i, j, k, i_, j_, k_);
                };

                try_add_b(-1, 0, 0);
                try_add_b(0, -1, 0);
                try_add_b(0, 0, -1);

                try_add_b(1, 0, 0);
                try_add_b(0, 1, 0);
                try_add_b(0, 0, 1);
            }
        }
    }
    return graph;
}
