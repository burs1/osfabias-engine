#include "vec2.h"

namespace osfeng::math {
  vec2::vec2(float p_x, float p_y) : x(p_x), y(p_y) {}

  vec2::vec2(const vec2& other) : x(other.x), y(other.y) {}

  // methods
  auto vec2::len() const -> float { return sqrt(x * x + y * y); }

  auto vec2::normalize() -> void {
    float length = len();
    x /= length; y /= length;
  }

  auto vec2::lerp(const vec2& other, float f) -> void {
    x = (other.x - x) * f;
    y = (other.y - y) * f;
  }

  auto vec2::rotate(float angle) -> void {
    float cosres = cos(angle);
    float sinres = sin(angle);
    float tx = x;

    x = x * cosres - y * sinres;
    y = tx * sinres + y * cosres;
  }

  auto vec2::drotate(float angle) -> void {
    rotate(angle * std::numbers::pi / 180);
  }

  // - static methods -
  auto vec2::normalized(const vec2& v) -> vec2 {
    float l = v.len();
    return vec2(v.x / l, v.y / l);
  }

  auto vec2::dot(const vec2& v1, const vec2& v2) -> float {
    return v1.x * v2.x + v1.y * v2.y;
  }

  auto vec2::lerp(const vec2& v1, const vec2& v2, float f) -> vec2 {
    return vec2((v2.x - v1.x) * f, (v2.y - v1.y) * f);  
  }

  auto vec2::rotated(const vec2 &v, float angle) -> vec2 {
    float cosres = cos(angle);
    float sinres = sin(angle);
    return vec2(v.x * cosres - v.y * sinres, v.x * sinres + v.y * cosres);
  }

  auto vec2::drotated(const vec2 &v, float angle) -> vec2 {
    return vec2::rotated(v, angle * std::numbers::pi / 180);
  }

  // - operators -
  auto vec2::operator=(const vec2& other) -> void {
    x = other.x;
    y = other.y;
  }

  auto vec2::operator+(const vec2 &other) const -> vec2 {
    return vec2(x + other.x, y + other.y);
  }

  auto vec2::operator+=(const vec2 &other) -> void {
    x += other.x;
    y += other.y;
  }

  auto vec2::operator-(const vec2 &other) const -> vec2 {
    return vec2(x - other.x, y - other.y);
  }

  auto vec2::operator-=(const vec2 &other) -> void {
    x -= other.x;
    y -= other.y;
  }

  auto vec2::operator*(const float &value) const -> vec2 {
    return vec2(x * value, y * value);
  }

  auto vec2::operator*=(const float &value) -> void {
    x *= value;
    y *= value;
  }

  auto vec2::operator/(const float &value) const -> vec2 {
    return vec2(x / value, y / value);
  }

  auto vec2::operator/=(const float &value) -> void {
    x /= value;
    y /= value;
  }

  auto vec2::operator==(const vec2 &other) const -> bool {
    return x == other.x && y == other.y;
  }

  auto vec2::operator!=(const vec2 &other) const -> bool {
    return not (*this == other);
  }
 
  auto vec2::operator>(const vec2 &other) const -> bool {
    return len() > other.len();
  }

  auto vec2::operator>=(const vec2 &other) const -> bool {
    return len() >= other.len();
  }

  auto vec2::operator<(const vec2 &other) const -> bool {
    return len() < other.len();
  }

  auto vec2::operator<=(const vec2 &other) const -> bool {
    return len() <= other.len();
  }

  vec2::operator std::string() const {
    return "(" + std::to_string(x) + " " + std::to_string(y) + ")";
  }
}
