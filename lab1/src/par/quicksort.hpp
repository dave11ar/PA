#pragma once

#include "../utils.hpp"

namespace par {

    template<typename It, typename Compare>
    void quicksort(It begin, It end, Compare comp) {
        tbb::task_arena task_arena(16);
        __quicksort_utils::par_quicksort(begin, end, comp, task_arena, 1000);
    }

    template<typename It>
    void quicksort(It begin, It end) {
        quicksort(begin, end, __quicksort_utils::Less());
    }

} // namespace par