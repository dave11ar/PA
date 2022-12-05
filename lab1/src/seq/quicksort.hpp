#pragma once

#include "../utils.hpp"

namespace seq {

    template<typename It, typename Compare>
    void quicksort(It begin, It end, Compare comp) {
        __quicksort_utils::seq_quicksort(begin, end, comp);
    }

    template<typename It>
    void quicksort(It begin, It end) {
        quicksort(begin, end, __quicksort_utils::Less());
    }
    
} // namespace seq