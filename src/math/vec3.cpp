#include "vec3.h"

namespace osfeng::math {
  vec3::vec3(float p_x, float p_y, float p_z)
    : x(p_x), y(p_y), z(p_z) {}

  vec3::vec3(const vec3& other)
    : x(other.x), y(other.y), z(other.z) {}

  // - methods -
  auto vec3::len() const -> float {
    return sqrtf(x * x + y * y + z * z);
  }

  auto vec3::normalize() -> void {
    float length = len();
    x /= length; y /= length; z /= length;
  }

  auto vec3::lerp(const vec3& other, float value) -> void {
    x = (other.x - x) * value;
    y = (other.y - y) * value;
    z = (other.z - z) * value;
 }

  // - statid methods -
  auto vec3::normalized(const vec3& v) -> vec3 {
    float length = v.len();
    return vec3(
      v.x / length,
      v.y / length,
      v.z / length
    );
  } 

  auto vec3::dot(const vec3& v1, const vec3& v2) -> float {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }

  auto vec3::cross(const vec3& v1, const vec3& v2) -> vec3 {
    return vec3(
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x
    );
  }

  auto vec3::lerp(const vec3& v1, const vec3& v2, float value)  -> vec3 {
    return vec3(
      (v2.x - v1.x) * value,
      (v2.y - v1.y) * value,
      (v2.z - v1.z) * value
    );
  }

  // - operators -
  auto vec3::operator=(const vec3& other) -> void {
    x = other.x;
    y = other.y;
    z = other.z;
  }

  auto vec3::operator+(const vec3 &other) const -> vec3 {
    return vec3(x + other.x, y + other.y, z + other.z);
  }

  auto vec3::operator+=(const vec3 &other) -> void {
    x += other.x;
    y += other.y;
    z += other.z;
  }

  auto vec3::operator-(const vec3 &other) const -> vec3 {
    return vec3(x - other.x, y - other.y, z - other.z);
  }

  auto vec3::operator-=(const vec3 &other) -> void {
    x -= other.x;
    y -= other.y;
    z -= other.z;
  }

  auto vec3::operator*(const float &value) const -> vec3 {
    return vec3(x * value, y * value, z * value);
  }

  auto vec3::operator*=(const float &value) -> void {
    x *= value;
    y *= value;
    z *= value;
  }

  auto vec3::operator/(const float &value) const -> vec3 {
    return vec3(x / value, y / value, z / value);
  }

  auto vec3::operator/=(const float &value) -> void {
    x /= value;
    y /= value;
    z /= value;
  }

  auto vec3::operator*=(const matrix4x4 &mtrx)       -> void {
    vec3 res = operator*(mtrx);
    x = res.x;
    y = res.y;
    z = res.z;
  }
  
  auto vec3::operator*(const matrix4x4 &mtrx) -> vec3 {
    vec3 res;
    res.x = x * mtrx.m[0][0] + y * mtrx.m[1][0] + z * mtrx.m[2][0] + mtrx.m[3][0];
    res.y = x * mtrx.m[0][1] + y * mtrx.m[1][1] + z * mtrx.m[2][1] + mtrx.m[3][1];
    res.z = x * mtrx.m[0][2] + y * mtrx.m[1][2] + z * mtrx.m[2][2] + mtrx.m[3][2];
    float w = x * mtrx.m[0][3] + y * mtrx.m[1][3] + z * mtrx.m[2][3] + mtrx.m[3][3];

    if (w != 0.0f) {
      res.x /= w;
      res.y /= w;
      res.z /= w;
    }

    return res;
  }

  auto vec3::operator==(const vec3 &other) const -> bool {
    return x == other.x && y == other.y && z == other.z;
  }

  auto vec3::operator!=(const vec3 &other) const -> bool {
    return !(*this == other);
  }

  auto vec3::operator>(const vec3 &other) const -> bool {
    return this->len() > other.len();
  }

  auto vec3::operator>=(const vec3 &other) const -> bool {
    return this->len() >= other.len();
  }

  auto vec3::operator<(const vec3 &other) const -> bool {
    return this->len() < other.len();
  }

  auto vec3::operator<=(const vec3 &other) const -> bool {
    return this->len() <= other.len();
  }

  vec3::operator std::string() const {
    return "(" + std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(z) + ")";
  }
}
