#pragma once

#include <cstl/common.h>

namespace cstl
{

template <typename T>
constexpr void swap(T &a, T &b) noexcept(noexcept(T(cstl::move(a))) && noexcept(a = cstl::move(b)) &&
                                         noexcept(b = cstl::move(a)))
{
    T temp = cstl::move(a);
    a = cstl::move(b);
    b = cstl::move(temp);
}

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
                swap(arr[j], arr[j + 1]);
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
            swap(arr[i], arr[largest]);
            self(self, arr, heap_size, largest);
        }
    };

    for (size_t i = n / 2; i-- > 0;)
    {
        heapify(heapify, arr, n, i);
    }

    for (size_t heap_size = n; heap_size > 1; --heap_size)
    {
        swap(arr[heap_size - 1], arr[0]);
        heapify(heapify, arr, heap_size - 1, 0);
    }
}

template <typename T> inline void quick_sort(T *arr, size_t n) noexcept
{
    auto partition = [](T *arr, size_t low, size_t high) noexcept -> size_t {
        T pivot = arr[high];
        int64_t i = low - 1;

        for (size_t j = low; j < high; j++)
        {
            if (arr[j] < pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    };

    auto quick_sort_rec = [&](auto &&self, T *arr, size_t low, size_t high) noexcept -> void {
        if (low < high)
        {
            size_t pi = partition(arr, low, high);
            self(self, arr, low, pi - 1);
            self(self, arr, pi + 1, high);
        }
    };

    quick_sort_rec(quick_sort_rec, arr, 0, n - 1);
}
} // namespace cstl
