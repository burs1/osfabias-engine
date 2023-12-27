#include "quaternion.h"

namespace osfeng::math {
  quaternion::quaternion(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

  quaternion::quaternion(const vec3 &v, float n) {}

  quaternion::quaternion(matrix4x4) {}

  // - methods -
  auto quaternion::len() const -> float {
    return sqrt(x*x + y*y + z*z + w*w);
  }
	
	auto quaternion::normalize() -> void {
	  float l = len();
	  x /= l; y /= l; z /= l; w /= l;
	}

	auto quaternion::lerp(const quaternion &other, float f) -> void {}

	auto quaternion::conjugate() -> void {
	  x *= -1; y *= -1; z *= -1;
	}

	auto quaternion::get_rotmat() const -> matrix4x4 {}

  auto quaternion::right() const -> vec3 {}

  auto quaternion::left() const -> vec3 {}

  auto quaternion::up() const -> vec3 {}

  auto quaternion::down() const -> vec3 {}

  auto quaternion::forward() const -> vec3 {}

  auto quaternion::back() const -> vec3 {}

  // - static methods -
  auto quaternion::normalized(const quaternion&) -> quaternion {}

  auto quaternion::dot(const quaternion&, const quaternion&) -> quaternion {}
  
  auto quaternion::lerp(const quaternion&, const quaternion&, float) -> quaternion {}

  auto conjugated(const quaternion& q) -> quaternion {
    return quaternion(-q.x, -q.y, -q.z, q.w);
  }

  // - operators -
  auto quaternion::operator=(quaternion q) -> void {
    x = q.x; y = q.y; z = q.z; w = q.z;
  }

  auto quaternion::operator+(quaternion q)  -> quaternion {
    return quaternion(x + q.x, y + q.y, z + q.z, w + q.w);
  }
  
  auto quaternion::operator+=(quaternion q) -> void {
    x += q.x; y += q.y; z += q.z; w += q.w;
  }

  auto quaternion::operator-(quaternion q) -> quaternion {
    return quaternion(x - q.x, y - q.y, z - q.z, w - q.w);
  }

  auto quaternion::operator-=(quaternion q) -> void {
    x -= q.x; y -= q.y; z -= q.z; w -= q.w;
  }

	auto quaternion::operator*(float v) -> quaternion {
	  return quaternion(x * v, y * v, z * v, w * v);
	}
	
	auto quaternion::operator*=(float v) -> void {
	  x *= v; y *= v; z *= v; w *= v;
	}

	auto quaternion::operator*(quaternion q) -> quaternion {
	  float xres = x * q.w + w * q.x + y * q.z - z * q.y;
	  float yres = z * q.w + w * q.y + z * q.x - x * q.z;
	  float zres = z * q.w + w * q.z + x * q.y - y * q.x;
	  float wres = w * q.w - x * q.x - y * q.y - z * q.z;

	  return quaternion(xres, yres, zres, wres);
	}
	
	auto quaternion::operator*=(quaternion q) -> void {
	  *this = operator*(q);
	}

	auto quaternion::operator*(vec3 v) -> quaternion {
	  float xres = w * v.x + y * v.z - z * v.y;
	  float yres = w * v.y + z * v.x - x * v.z;
	  float zres = w * v.z + x * v.y + y * v.x;
	  float wres = -x * v.x - y * v.y - z * v.z;

	  return quaternion(xres, yres, zres, wres);
	}
	
	auto quaternion::operator*=(vec3 v) -> void {
	  *this = operator*(v);
	}
}
