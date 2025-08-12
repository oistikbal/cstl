#pragma once

#include "common.h"

namespace cstl
{
template <typename T> inline void insertion_sort(T *arr, size_t size) noexcept
{
    for (size_t i = 1; i < size; i++)
    {
        T key = arr[i];
        int64_t j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}
} // namespace cstl
