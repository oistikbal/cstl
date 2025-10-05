#pragma once

#include <cstl/common.h>

namespace cstl
{
template <typename T> class stack
{

  public:
    constexpr stack() noexcept = default;
    constexpr ~stack() noexcept
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

    constexpr void push(const T &value)
    {
        if (m_size == m_capacity)
            grow();
        new (m_data + m_size) T(value);
        ++m_size;
    }

    constexpr void push(T &&value)
    {
        if (m_size == m_capacity)
            grow();
        new (m_data + m_size) T(static_cast<T &&>(value));
        ++m_size;
    }

    constexpr void pop()
    {
        assert(m_size > 0 && "cstl::stack::pop, empty stack");
        m_data[m_size - 1].~T();
        --m_size;
    }

    [[nodiscard]] constexpr T &top() noexcept
    {
        assert(m_size > 0 && "cstl::stack::top, empty stack");
        return m_data[m_size - 1];
    }

    [[nodiscard]] constexpr const T &top() const noexcept
    {
        assert(m_size > 0 && "cstl::stack::top, empty stack");
        return m_data[m_size - 1];
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