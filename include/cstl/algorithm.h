#pragma once

#include <cstl/common.h>

namespace cstl
{
template <typename T> inline void insertion_sort(T *arr, size_t n) noexcept
{
    for (size_t i = 1; i < n; i++)
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

template <typename T> inline void merge_sort(T *arr, size_t n) noexcept
{
    auto internal_sort = [&](auto &&self, T *arr, size_t n) noexcept -> void {
        if (n <= 1)
            return;

        size_t mid = n / 2;

        self(self, arr, mid);
        self(self, arr + mid, n - mid);

        size_t n1 = mid;
        size_t n2 = n - mid;

        T *L = new T[n1];
        T *R = new T[n2];

        for (size_t i = 0; i < n1; i++)
            L[i] = arr[i];
        for (size_t j = 0; j < n2; j++)
            R[j] = arr[mid + j];

        size_t i = 0, j = 0, k = 0;
        while (i < n1 && j < n2)
        {
            arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
        }
        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];

        delete[] L;
        delete[] R;
    };

    internal_sort(internal_sort, arr, n);
}

template <typename T> inline void bubble_sort(T *arr, size_t n) noexcept
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

template <typename T> inline void heap_sort(T *arr, size_t n) noexcept
{
    auto heapify = [](auto &&self, T *arr, size_t heap_size, size_t i) noexcept -> void {
        size_t largest = i;
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;

        if (left < heap_size && arr[left] > arr[largest])
            largest = left;
        if (right < heap_size && arr[right] > arr[largest])
            largest = right;

        if (largest != i)
        {
            T temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            self(self, arr, heap_size, largest);
        }
    };

    for (size_t i = n / 2; i-- > 0;)
    {
        heapify(heapify, arr, n, i);
    }

    for (size_t heap_size = n; heap_size > 1; --heap_size)
    {
        T temp = arr[0];
        arr[0] = arr[heap_size - 1];
        arr[heap_size - 1] = temp;

        heapify(heapify, arr, heap_size - 1, 0);
    }
}
} // namespace cstl
