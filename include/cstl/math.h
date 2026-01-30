#pragma once

#include <smmintrin.h>
#include <xmmintrin.h>

namespace cstl
{

constexpr float pi = 3.141592654f;
constexpr float rad_to_deg = 180.0f / pi;
constexpr float deg_to_rad = pi / 180.0f;

using vector3 = __m128;
using vector4 = __m128;


struct alignas(16) float3
{
    float x;
    float y;
    float z;

    float3() = default;

    float3(const float3 &) = default;
    float3 &operator=(const float3 &) = default;

    float3(float3 &&) = default;
    float3 &operator=(float3 &&) = default;

    constexpr float3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z)
    {
    }
};

static_assert(sizeof(float3) == 16, "Size of float3 must be 16");

inline float sqrt(float x)
{
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}

inline float3 float3_get(const vector3 &v)
{
    float3 f;
    _mm_store_ps(reinterpret_cast<float *>(&f), v);
    return f;
}

inline vector3 vector3_get(const float3 &f)
{
    return _mm_load_ps(reinterpret_cast<const float *>(&f));
}

inline float vector3_dot(const vector3 &v1, const vector3 &v2)
{
    return _mm_cvtss_f32(_mm_dp_ps(v1, v2, 0x77));
}

inline float float3_length(const float3 &f)
{
    return sqrt(f.x * f.x + f.y * f.y + f.z * f.z);
}

inline float3 float3_normal(const float3 &f)
{
    float inv_l = _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(f.x * f.x + f.y * f.y + f.z * f.z)));

    return float3(f.x * inv_l, f.y * inv_l, f.z * inv_l);
}

inline float float3_dot(const float3 &f1, const float3 &f2)
{
    return vector3_dot(vector3_get(f1), vector3_get(f2));
}


} // namespace cstl