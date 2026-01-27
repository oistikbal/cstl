#pragma once

#include <cstl/common.h>

namespace cstl
{
template <typename T> class queue
{
  public:
    constexpr queue() noexcept = default;

    constexpr explicit queue(size_t capacity) noexcept : m_capacity(capacity), m_data(new T[capacity])
    {
    }

    constexpr ~queue() noexcept
    {
        destroy();
    }

    constexpr void clear() noexcept
    {
        m_size = 0;
        m_head = 0;
        m_tail = 0;
    }

    constexpr void push(const T &value)
    {
        ensure_capacity();
        m_data[m_tail] = value;
        m_tail = (m_tail + 1) % m_capacity;
        ++m_size;
    }

    constexpr void push(T &&value)
    {
        ensure_capacity();
        m_data[m_tail] = static_cast<T &&>(value);
        m_tail = (m_tail + 1) % m_capacity;
        ++m_size;
    }

    constexpr void pop() noexcept
    {
        assert(!empty() && "cstl::queue::pop, queue empty");
        m_head = (m_head + 1) % m_capacity;
        --m_size;
    }

    [[nodiscard]] constexpr T &front() noexcept
    {
        assert(!empty() && "cstl::queue::front, queue empty");
        return m_data[m_head];
    }

    [[nodiscard]] constexpr const T &front() const noexcept
    {
        assert(!empty() && "cstl::queue::front, queue empty");
        return m_data[m_head];
    }

    [[nodiscard]] constexpr T &back() noexcept
    {
        assert(!empty() && "cstl::queue::back, queue empty");
        size_t idx = (m_tail + m_capacity - 1) % m_capacity;
        return m_data[idx];
    }

    [[nodiscard]] constexpr const T &back() const noexcept
    {
        assert(!empty() && "cstl::queue::back, queue empty");
        size_t idx = (m_tail + m_capacity - 1) % m_capacity;
        return m_data[idx];
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return m_size == 0;
    }

    [[nodiscard]] constexpr size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] constexpr size_t capacity() const noexcept
    {
        return m_capacity;
    }

    constexpr void destroy() noexcept
    {
        clear();
    }

private:
    constexpr void ensure_capacity()
    {
        if (m_capacity == 0)
        {
            m_capacity = 4;
            m_data = new T[m_capacity];
            return;
        }

        if (m_size < m_capacity)
            return;

        size_t new_capacity = m_capacity * 2;
        T *new_data = new T[new_capacity];

        for (size_t i = 0; i < m_size; ++i)
        {
            new_data[i] = cstl::move(m_data[(m_head + i) % m_capacity]);
        }

        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
        m_head = 0;
        m_tail = m_size;
    }

  private:
    T *m_data = nullptr;
    size_t m_capacity = 0;
    size_t m_size = 0;
    size_t m_head = 0;
    size_t m_tail = 0;
};
} // namespace cstl