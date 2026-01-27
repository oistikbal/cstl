#pragma once

#include <xmmintrin.h>

namespace cstl
{

constexpr float pi = 3.141592654f;
constexpr float rad_to_deg = 180.0f / pi;
constexpr float deg_to_rad = pi / 180.0f;

inline float sqrt(float x)
{
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

struct vector3
{
    float x;
    float y;
    float z;

    vector3() = default;

    vector3(const vector3 &) = default;
    vector3 &operator=(const vector3 &) = default;

    vector3(vector3 &&) = default;
    vector3 &operator=(vector3 &&) = default;

    constexpr vector3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z)
    {
    }

    inline float length() const noexcept
    {
        return sqrt(x * x + y * y + z * z);
    }

    inline vector3 normal() const noexcept
    {
        float inv_l = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(x * x + y * y + z * z)));

        return vector3(x * inv_l, y * inv_l, z * inv_l);
    }
};
} // namespace cstl