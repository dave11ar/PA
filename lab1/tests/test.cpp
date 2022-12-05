#include <algorithm>

#include <gtest/gtest.h>
#include <random>

#include "../src/seq/quicksort.hpp"
#include "../src/par/quicksort.hpp"



void check_qsort(std::vector<uint32_t> vec_sort, std::function<void(std::vector<uint32_t>&)> fun) {
    auto vec_qsort = vec_sort;

    std::sort(vec_sort.begin(), vec_sort.end());
    fun(vec_qsort);

    EXPECT_EQ(vec_sort, vec_qsort);
}

void check_both_qsorts(const std::vector<uint32_t>& vec) {
    check_qsort(vec, [](std::vector<uint32_t>& v){seq::quicksort(v.begin(), v.end());});
    check_qsort(vec, [](std::vector<uint32_t>& v){par::quicksort(v.begin(), v.end());});
}

TEST(Unit, DifferentValues) {
    check_both_qsorts({2, 3, 1, 100, 4, 55, 33, 53, 22});
}

TEST(Unit, RepeatingValues) {
    check_both_qsorts({2, 3, 1, 1, 4, 4, 2, 3, 22});
}

TEST(Stress, Big) {
    constexpr size_t AMOUNT = 1000;
    constexpr size_t SIZE = 10000;

    std::mt19937 gen;
    
    for (size_t i = 0; i < AMOUNT; ++i) {
        std::vector<uint32_t> vec(SIZE);
        for (size_t j = 0; j < SIZE; ++j) {
            vec[j] = gen();
        }

        check_both_qsorts(vec);
    }
}