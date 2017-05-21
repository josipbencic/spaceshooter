#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>

namespace math {

  class vec3 {

    friend vec3 operator+ (const vec3& left, const vec3& right);
    friend vec3 operator- (const vec3& left, const vec3& right);
    friend inline float dot(const vec3& a, const vec3& b);
    friend vec3 operator* (const float scalar, const vec3& vector);
    friend inline vec3 normalize (const vec3& a);

  public:
    vec3() : x(0.0f), y(0.0f), z(0.0f) {}

    vec3(float x, float y, float z)
      : x(x), y(y), z(z)
    {}

    vec3(const vec3& src)
      : x(src.x), y(src.y), z(src.z)
    {}

    const vec3& operator+= (const vec3& rhs) {
      x += rhs.x;
      y += rhs.y;
      z += rhs.z;
      return *this;
    }

    const vec3& operator-= (const vec3& rhs) {
      x -= rhs.x;
      y -= rhs.y;
      z -= rhs.z;
      return *this;
    }

    bool operator== (const vec3& rhs) {
      return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!= (const vec3& rhs) {
      return !(*this).operator==(rhs);
    }


    vec3 operator- (const vec3& rhs) {
      return vec3(-rhs.x, -rhs.y, -rhs.z);
    }

    vec3& normalize() {
      float d = sqrt(x*x + y*y + z*z);
      x /= d;
      y /= d;
      z /= d;
      return *this;
    }

    const vec3& operator= (const vec3& rhs) {
      x = rhs.x;
      y = rhs.y;
      z = rhs.z;
      return *this;
    }

    float x, y, z;
  };

  inline vec3 point(float x, float y) {
    return vec3(x, y, 1.0f);
  }

  inline vec3 vector(float x, float y) {
    return vec3(x, y, 0.0f);
  }

  inline vec3 operator* (const float scalar, const vec3& vector) {
    return vec3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
  }

  inline vec3 operator+ (const vec3& left, const vec3& right) {
    return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
  }

  inline vec3 operator- (const vec3& left, const vec3& right) {
    return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
  }

  inline float dot(const vec3& a, const vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  inline vec3 normalize(const vec3& a) {
    float d = sqrt(abs(a.x*a.x + a.y*a.y + a.z*a.z));
    return vec3(a.x/d, a.y/d, a.z/d);;
  }
}

#endif