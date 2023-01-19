#pragma once

#include <atomic>
#include <deque>
#include <limits>
#include <cstddef>
#include <vector>
#include "utils.hpp"
#include <parlay/primitives.h>
#include <parlay/parallel.h>

inline void seq_bfs(int32_t start, std::vector<int32_t>& distance, const std::vector<std::vector<int32_t>>& edges) {
    std::deque<int32_t> q{start};
    distance[start] = 0;

    while (!q.empty()){
        int32_t v = q.front();
        q.pop_front();

        for (int32_t u : edges[v]) {
            if (distance[u] == -1) {
                distance[u] = distance[v] + 1;
                q.push_back(u);
            }
        }
    }
}

inline void par_bfs(int32_t start, std::vector<int32_t>& distance, const std::vector<std::vector<int32_t>>& edges) {
    distance[start] = 0;

    parlay::sequence<std::atomic_bool> visited(distance.size());
    visited[start].store(true, std::memory_order_release);

    parlay::sequence<int32_t> frontier(1, start);
    int32_t frontier_number = 0;

    while (!frontier.empty()) {
        frontier = filter(
            flatten(map(frontier, [&edges](int32_t i){return edges[i];})), 
            [&visited](int32_t i) {
                return !visited[i].exchange(true, std::memory_order_acq_rel);
            });

        ++frontier_number;
        parlay::parallel_for(0, frontier.size(), 
            [&distance, &frontier, frontier_number](int32_t i) {
                distance[frontier[i]] = frontier_number;
            }
        );
    }
}