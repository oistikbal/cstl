#pragma once

#include <cstl/common.h>

namespace cstl
{
template <typename T> class vector
{
  public:
    explicit vector(size_t count)
    {
        reserve(count);
        for (size_t i = 0; i < count; ++i)
            new (m_data + i) T();
    }

    ~vector()
    {
        clear();
        destroy();
    }

    constexpr void clear() noexcept
    {
        for (size_t i = 0; i < m_size; ++i)
            m_data[i].~T();
        m_size = 0;
    }

    [[nodiscard]] constexpr T &operator[](size_t i) noexcept
    {
        assert(i < m_size && "cstl::vector::operator[], index out of range");
        return m_data[i];
    }

    [[nodiscard]] constexpr const T &operator[](size_t i) const noexcept
    {
        assert(i < m_size && "cstl::vector::operator[], index out of range");
        return m_data[i];
    }

    constexpr void push_back(const T &value)
    {
        if (m_size == m_capacity)
            grow();
        new (m_data + m_size) T(value);
        ++m_size;
    }

    constexpr void push_back(T &&value)
    {
        if (m_size == m_capacity)
            grow();
        new (m_data + m_size) T(static_cast<T &&>(value));
        ++m_size;
    }

    constexpr void pop_back()
    {
        assert(m_size > 0 && "cstl::vector::pop_back, empty vector");
        m_data[m_size - 1].~T();
        --m_size;
    }

    [[nodiscard]] constexpr T &front() noexcept
    {
        assert(m_size > 0 && "cstl::vector::front, empty vector");
        return m_data[0];
    }

    [[nodiscard]] constexpr const T &front() const noexcept
    {
        assert(m_size > 0 && "cstl::vector::front, empty vector");
        return m_data[0];
    }

    [[nodiscard]] constexpr T &back() noexcept
    {
        assert(m_size > 0 && "cstl::vector::back, empty vector");
        return m_data[m_size - 1];
    }

    [[nodiscard]] constexpr const T &back() const noexcept
    {
        assert(m_size > 0 && "cstl::vector::back, empty vector");
        return m_data[m_size - 1];
    }

    [[nodiscard]] constexpr T *data() noexcept
    {
        return m_data;
    }

    [[nodiscard]] constexpr const T *data() const noexcept
    {
        return m_data;
    }

    [[nodiscard]] constexpr size_t size() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] constexpr size_t capacity() const noexcept
    {
        return m_capacity;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return m_size == 0;
    }

    void reserve(size_t new_cap)
    {
        if (new_cap <= m_capacity)
            return;

        T *new_data = static_cast<T *>(::operator new(sizeof(T) * new_cap));
        for (size_t i = 0; i < m_size; ++i)
        {
            new (new_data + i) T(static_cast<T &&>(m_data[i]));
            m_data[i].~T();
        }
        ::operator delete(m_data);
        m_data = new_data;
        m_capacity = new_cap;
    }

    void resize(size_t new_size)
    {
        if (new_size > m_capacity)
            reserve(new_size);
        if (new_size > m_size)
            for (size_t i = m_size; i < new_size; ++i)
                new (m_data + i) T();
        else
            for (size_t i = new_size; i < m_size; ++i)
                m_data[i].~T();
        m_size = new_size;
    }

  private:
    constexpr void grow()
    {
        size_t new_cap = (m_capacity == 0) ? 1 : (m_capacity * 2);
        reserve(new_cap);
    }

    constexpr void destroy() noexcept
    {
        operator delete(m_data);
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

  private:
    T *m_data;
    size_t m_size = 0;
    size_t m_capacity = 0;
};
} // namespace cstl