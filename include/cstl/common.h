#pragma once

#define __STDC_LIMIT_MACROS

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <cstddef>
#include <cstdint>

namespace cstl
{
template <typename T> struct remove_reference
{
    using type = T;
};
template <typename T> struct remove_reference<T &>
{
    using type = T;
};
template <typename T> struct remove_reference<T &&>
{
    using type = T;
};

template <typename T> using remove_reference_t = typename remove_reference<T>::type;

template <typename T> constexpr T &&forward(remove_reference_t<T> &value) noexcept
{
    return static_cast<T &&>(value);
}

template <typename T> constexpr remove_reference_t<T> &&move(T &&value) noexcept
{
    return static_cast<remove_reference_t<T> &&>(value);
}
} // namespace cstl