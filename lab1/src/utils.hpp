#pragma once

#include <iostream>
#include <random>

#include <tbb/tbb.h>

namespace __quicksort_utils {

    struct Less {
        template<typename T>
        bool operator()(const T& a, const T& b) const {
            return a < b;
        }
    };


    
    template<typename It, typename Compare>
    It hoare_partition(It begin, It end, const Compare& comp) {
        const auto piv = *begin;

        --end;
        while (begin <= end) {
            while (comp(*begin, piv)) {
                ++begin;
            }
            while (comp(piv, *end)) {
                --end;
            }
            if (begin >= end) {
                break;
            }
            if (begin != end) {
                std::iter_swap(begin, end);
                ++begin;
                --end;
            }
        }
        return end + 1;
    }

    template<typename It, typename Compare>
    void seq_quicksort(It begin, It end, const Compare& comp) {
        if (end - begin < 2) {
            return;
        }

        const auto partition = hoare_partition(begin, end, comp);
        seq_quicksort(begin, partition, comp);
        seq_quicksort(partition, end, comp);
    }

    template<typename It, typename Compare>
    void par_quicksort(It begin, It end, const Compare& comp, tbb::task_arena& task_arena, size_t border) {
        if (end - begin < 2) {
            return;
        }

        const auto partition = hoare_partition(begin, end, comp);
        task_arena.execute(
            [&](){
                tbb::parallel_invoke(
                    [&](){par_quicksort(begin, partition, comp, task_arena, border);},
                    [&](){par_quicksort(partition, end, comp, task_arena, border);});
            });
    }

} // namespace __quicksort_utils