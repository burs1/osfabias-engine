#include "matrix4x4.h"

namespace osfeng::math {
  matrix4x4::matrix4x4() { set_identity(); }

  matrix4x4::matrix4x4(const matrix4x4& other) { _copy(other); }

  // methods
  auto matrix4x4::set_identity() -> void {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j)
        m[i][j] = i == j;
    }
  }

  auto matrix4x4::set_translation(const vec3& v) -> void {
    m[0][0] = 1.0f;
    m[1][1] = 1.0f;
    m[2][2] = 1.0f;
    m[3][3] = 1.0f;
    m[3][0] = v.x;
    m[3][1] = v.y;
    m[3][2] = v.z;
  }

  auto matrix4x4::set_scale(const vec3& v) -> void {
    m[0][0] = v.x;
    m[1][1] = v.y;
    m[2][2] = v.z;
  }

  auto matrix4x4::set_rot(const vec3& v) -> void {
  }

  auto matrix4x4::set_perspective(float fov, float aspratio, float near, float far) -> void {
    float fovrad = 1.0f / tanf( (fov / 2) * (3.14159f / 180) );
		m[0][0] = aspratio * fovrad;
		m[1][1] = fovrad;
		m[2][2] = far / (far - near);
		m[2][3] = 1.0f;
		m[3][2] = -near * m[2][2];
		m[3][3] = 0.0f;
	}
  
  // operators
	auto matrix4x4::operator*=(const matrix4x4& other) -> void {
	  _copy( operator*(other) );
	}
  
  auto matrix4x4::operator*(const matrix4x4& other) const -> matrix4x4 {
    matrix4x4 res;

    for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 4; r++) {
			  res.m[r][c] =
			    m[r][0] * other.m[0][c] +
			    m[r][1] * other.m[1][c] +
			    m[r][2] * other.m[2][c] + 
			    m[r][3] * other.m[3][c];
			}
		}

		return res;
  }

	auto matrix4x4::operator=(const matrix4x4& other) -> void {
	  _copy(other);
	}

  // internal methods
  auto matrix4x4::_copy(const matrix4x4& other) -> void {
	  for (int i = 0; i < 4; ++i) {
	    for (int j = 0; j < 4; ++j) { m[i][j] = other.m[i][j]; }
	  }
	}

}
