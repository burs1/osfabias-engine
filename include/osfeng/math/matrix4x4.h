#pragma once

#include "vec3.h"

namespace osfeng::math {
  class vec3;
  class matrix4x4 {
  public:
    matrix4x4();

    matrix4x4(const matrix4x4&);

    // methods
    auto set_identity()                                             -> void;

    auto set_translation(const vec3&)                               -> void;

    auto set_translation(float, float, float)                       -> void;

    auto set_rot(const vec3&)                                       -> void;

    auto set_rot(float, float, float)                               -> void;
    
    auto set_rot(const vec3&, const vec3&)                          -> void;

    auto set_rot(const vec3&, const vec3&, const vec3&)             -> void;

    auto set_scale(const vec3&)                                     -> void;

    auto set_perspective(float, float, float, float)                -> void;

    auto set_orthographic(float, float, float, float, float, float) -> void;

    // operators
    auto operator*=(const matrix4x4&)       -> void;
    
    auto operator*(const matrix4x4&)  const -> matrix4x4;

    auto operator=(const matrix4x4&)        -> void;

    // vars
    float m[4][4];

  private:
    // internal methods
    auto _copy(const matrix4x4&) -> void;
  };
}
