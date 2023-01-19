#include <gtest/gtest.h>

#include "../src/utils.hpp"
#include "../src/bfs.hpp"

TEST(amo, gus) {    
    const auto qubic500 = generate_qubic_graph(200);
    std::vector<int32_t> distance_seq(qubic500.size(), -1);
    std::vector<int32_t> distance_par(qubic500.size(), -1);

    seq_bfs(0, distance_seq, qubic500);
    par_bfs(0, distance_par, qubic500);

    ASSERT_EQ(distance_seq, distance_par);
}