#ifndef MATH_COLLISION_HPP
#define MATH_COLLISION_HPP

#include "../Math/vec3.hpp"
#include "../Math/constants.hpp"

namespace math {

  /*
    Some algorithms for simple AABB, circle and point collision.

    TODO: Separating Axis Theorem application on arbitary polygon if needed
  */

  /*
    Returns squared distance between two points.
    (helper function)
  */
  inline float dist_sqr(vec3 a, vec3 b) {
    return  (a.x - b.x) * (a.x - b.x) +
            (a.y - b.y) * (a.y - b.y);
  }

  /*
    Resolves collision between circle and point.
  */
  inline bool circle_point(vec3 center, float radius, vec3 point) {
    return  dist_sqr(center, point) < radius * radius;
  }

  /*
    Resolves collision between rectangle and point.
  */
  inline bool rect_point(vec3 low_left, vec3 up_right, vec3 point) {
    return  point.x < up_right.x &&
        point.x > low_left.x &&
        point.y < up_right.y &&
        point.y > low_left.y;
  }

  /*
    Resolves collision between two rectangles.
  */
  inline bool rect_rect(
    vec3 a_low_left, vec3 a_up_right,
    vec3 b_low_left, vec3 b_up_right) {

    return  !(a_low_left.x > b_up_right.x ||
        a_up_right.x < b_low_left.x ||
        a_low_left.y > b_up_right.y ||
        a_up_right.y < b_low_left.y);
  }


  /*
    Resolves collision between two circles.
  */
  inline bool circle_circle(
    vec3 center_a, float radius_a,
    vec3 center_b, float radius_b) {
    return  dist_sqr(center_a, center_b) <
            (radius_a + radius_b) * (radius_a + radius_b);
  }

  inline bool circle_rect(
    vec3 center, float radius,
    vec3 rect_min, vec3 rect_max) {

    return  rect_point(rect_min, rect_max, center) ||
        circle_point(center, radius, rect_min) ||
        circle_point(center, radius, rect_max) ||
        circle_point(center, radius, point(rect_min.x, rect_max.y)) ||
        circle_point(center, radius, point(rect_min.y, rect_max.x));
  }
}

#endif