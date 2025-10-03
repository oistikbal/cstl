#pragma once

#include <cstl/common.h>

namespace cstl
{
template <typename T, size_t _size> class array
{
  public:
    [[nodiscard]] constexpr T &operator[](size_t i) noexcept
    {
        assert(i < _size && "cstl::array::operator[], index out of range");
        return m_data[i];
    }

    [[nodiscard]] constexpr const T &operator[](size_t i) const noexcept
    {
        assert(i < _size && "cstl::array::operator[], index out of range");
        return m_data[i];
    }

    [[nodiscard]] constexpr T &at(size_t i)
    {
        assert(i < _size && "cstl::array::at, index out of range");
        return m_data[i];
    }

    constexpr void fill(const T &value)
    {
        for (size_t i = 0; i < _size; ++i)
            m_data[i] = value;
    }

    constexpr T &front() noexcept
    {
        return m_data[0];
    }
    constexpr const T &front() const noexcept
    {
        return m_data[0];
    }

    constexpr T &back() noexcept
    {
        return m_data[_size - 1];
    }
    constexpr const T &back() const noexcept
    {
        return m_data[_size - 1];
    }

    [[nodiscard]] constexpr size_t size() const noexcept
    {
        return _size;
    }

    [[nodiscard]] constexpr bool empty() const noexcept
    {
        return _size == 0;
    }

    constexpr T *data() noexcept
    {
        return m_data;
    }
    constexpr const T *data() const noexcept
    {
        return m_data;
    }

  private:
    T m_data[_size];
};
} // namespace cstl