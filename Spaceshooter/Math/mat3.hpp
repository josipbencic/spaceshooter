#ifndef MAT3_HPP
#define MAT3_HPP

#include "../Math/vec3.hpp"
#include <cmath>

namespace math {

  class mat3 {

    friend inline vec3 operator* (const mat3& mat, const vec3& vec);
    friend inline mat3 operator* (const mat3& left, const mat3& right);
    friend inline mat3 operator+ (const mat3& a, const mat3& b);
    friend inline mat3 operator- (const mat3& a, const mat3& b);
    friend inline mat3 rotate(float angle_in_radians); //  angle has to between 0 and half Pi
    friend inline mat3 translate(const vec3& vec);
    friend inline mat3 scale(const vec3& coeff);
    friend inline mat3 scale(float coeff);

  public:
    mat3() {
      for (unsigned i = 0; i < 9; i++)
        data[i] = 0;
    }

    mat3(float x) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = 0;
      data[0] = data[4] = data[8] = x;
    }

    mat3(const mat3& src) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = src.data[i];
    }

    mat3& operator= (const mat3& rhs) {
      for (unsigned i = 0; i < 9; i++)
        data[i] = rhs.data[i];
      return *this;
    }

    float data[9];
  };

  inline mat3 operator-(const mat3& a, const mat3& b) {
    mat3 ret;
    for (unsigned i = 0; i < 9; i++)
      ret.data[i] = a.data[i] - b.data[i];
    return ret;
  }

  inline mat3 operator+(const mat3& a, const mat3& b) {
    mat3 ret;
    for (unsigned i = 0; i < 9; i++)
      ret.data[i] = a.data[i] + b.data[i];
    return ret;
  }

  inline mat3 operator*(const mat3& left, const mat3& right) {
    mat3 ret;
    for (unsigned i = 0; i < 3; i++)
      for (unsigned j = 0; j < 3; j++)
        for (unsigned k = 0; k < 3; k++)
          ret.data[i * 3 + j] += left.data[i * 3 + k] * right.data[j * 3 + k];
    return ret;
  }

  inline vec3 operator*(const mat3& mat, const vec3& vec) {
    return vec3(
      mat.data[0] * vec.x + mat.data[1] * vec.y + mat.data[2] * vec.z,
      mat.data[3] * vec.x + mat.data[4] * vec.y + mat.data[5] * vec.z,
      mat.data[6] * vec.x + mat.data[7] * vec.y + mat.data[8] * vec.z);
  }

  inline mat3 scale(float coeff) {
    mat3 ret;
    ret.data[0] = ret.data[4] = ret.data[8] = coeff;
    return ret;
  }

  inline mat3 scale(const vec3& coeff) {
    mat3 ret;
    ret.data[0] = coeff.x;
    ret.data[4] = coeff.y;
    ret.data[8] = 1;
    return ret;
  }

  inline mat3 translate(const vec3& vec) {
    mat3 ret;
    ret.data[2] = vec.x;
    ret.data[5] = vec.y;
    ret.data[8] = ret.data[4] = ret.data[0] = 1;
    return ret;
  }

  inline mat3 rotate(float angle) {
    float c = cos(angle);
    float s = sin(angle);
    mat3 ret;
    ret.data[0] = ret.data[4] = c;
    ret.data[1] = -s;
    ret.data[3] = s;
    ret.data[8] = 1;
    return ret;
  }
}

#endif