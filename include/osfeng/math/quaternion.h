#pragma once

#include "vec3.h"
#include "matrix4x4.h"

namespace osfeng::math {
  class quaternion {
  public:
	  explicit quaternion(float x=0, float y=0, float z=0, float w=0);

    quaternion(const vec3&, float);

    quaternion(matrix4x4);

    // - methods -
    auto len()                    const -> float;
	  
	  auto normalize()                    -> void;

	  auto lerp(const quaternion&, float) -> void;

	  auto conjugate()                    -> void;

	  auto get_rotmat()             const -> matrix4x4;

    auto right()                  const -> vec3;

    auto left()                   const -> vec3;

    auto up()                     const -> vec3;

    auto down()                   const -> vec3;

    auto forward()                const -> vec3;

    auto back()                   const -> vec3;

    // - static methods -
    static auto normalized(const quaternion&)                     -> quaternion;

    static auto dot(const quaternion&, const quaternion&)         -> quaternion;
    
    static auto lerp(const quaternion&, const quaternion&, float) -> quaternion;

    static auto conjugated(const quaternion&)                     -> quaternion;

    // - operators -
    auto operator=(quaternion)  -> void;

    auto operator+(quaternion)  -> quaternion;
    
    auto operator+=(quaternion) -> void;

    auto operator-(quaternion)  -> quaternion;

    auto operator-=(quaternion) -> void;

	  auto operator*(float)       -> quaternion;
	  
	  auto operator*=(float)      -> void;

	  auto operator*(quaternion)  -> quaternion;
	  
	  auto operator*=(quaternion) -> void;

	  auto operator*(vec3)        -> quaternion;
	  
	  auto operator*=(vec3)       -> void;

	  // - vars -
    float x, y, z, w;
  };
}
