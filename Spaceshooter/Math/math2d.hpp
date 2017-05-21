#ifndef MATH_HPP
#define MATH_HPP

#include "../Math/vec3.hpp"
#include "../Math/mat3.hpp"
#include "../Math/constants.hpp"
#include "../Math/collision.hpp"

namespace math {

  inline float radians(float angle) {
    return PI_DIV_180 * angle;
  }

  inline float degrees(float angle) {
    return PI_DIV_180_INVERSE * angle;
  }

  #ifdef max
    #undef max
  #endif

  template<typename __PartiallyOrdered__>
  inline __PartiallyOrdered__
  max(
    __PartiallyOrdered__ a,
    __PartiallyOrdered__ b) {

    return a < b ? b : a;
  }

  template<typename __PartiallyOrdered__>
  inline __PartiallyOrdered__
  min(
    __PartiallyOrdered__ a,
    __PartiallyOrdered__ b) {

    return a > b ? b : a;
  }

  /*
    Rescales a given number from its range to a
    specified one.
  */
  template<typename __DivisionAlgebra__>
  inline __DivisionAlgebra__
  remap(
    __DivisionAlgebra__ number,
    __DivisionAlgebra__ low,
    __DivisionAlgebra__ high,
    __DivisionAlgebra__ new_low,
    __DivisionAlgebra__ new_high) {

    return (number - low) * (new_high - new_low) / (high - low) + new_low;
  }

  /*
    Linear Interpolation

    Defined on any algebraic structure supporting
    scalar multiplication and addition.
  */
  template<typename __VectorSpace__>
  inline __VectorSpace__
  lerp(
    __VectorSpace__ from,
    __VectorSpace__ to,
    float scalar) {

    return (1.0f - scalar) * from + scalar * to;
  }

  template<typename __PartiallyOrdered__>
  inline bool
  is_between(
    __PartiallyOrdered__ x,
    __PartiallyOrdered__ lo,
    __PartiallyOrdered__ hi) {

    return x <= hi && x >= lo;
  }

  inline float clamp_to_01(float x) {
    if (x > 1.0f) return 1.0f;
    if (x < 0.0f) return 0.0f;
    return x;
  }
}

#endif
