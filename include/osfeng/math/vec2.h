#pragma once

#include <cmath>
#include <string>
#include <numbers>

namespace osfeng::math {
  class vec2 {
  public:
    explicit vec2(float p_x = 0, float p_y = 0);
    
    vec2(const vec2&);

    // - methods - 
    auto len()                      const -> float;

    auto normalize()                      -> void;

    auto lerp(const vec2&, float value)   -> void;

    auto rotate(float)                    -> void;

    auto drotate(float)                   -> void;

    // - static methods -
    static auto normalized(const vec2&)                       -> vec2;

    static auto dot(const vec2&, const vec2&)                 -> float;

    static auto lerp(const vec2&, const vec2&, float value)   -> vec2;

    static auto rotated(const vec2&, float)                   -> vec2;

    static auto drotated(const vec2&, float)                  -> vec2;

    // - operatos -
    auto operator=(const vec2&)           -> void;

    auto operator+(const vec2&)     const -> vec2;

    auto operator+=(const vec2&)          -> void;

    auto operator-(const vec2&)     const -> vec2;

    auto operator-=(const vec2&)          -> void;

    auto operator*(const float&)    const -> vec2;
    
    auto operator*=(const float &)        -> void;
    
    auto operator/(const float&)    const -> vec2;

    auto operator/=(const float&)         -> void;
  
    auto operator*(const vec2&)     const -> float;

    auto operator==(const vec2&)    const -> bool;

    auto operator!=(const vec2&)    const -> bool;
    
    auto operator>(const vec2&)     const -> bool;

    auto operator>=(const vec2&)    const -> bool;

    auto operator<(const vec2&)     const -> bool;

    auto operator<=(const vec2&)    const -> bool;

    operator std::string() const;

    // - vars -
    float x, y;
  };
}
