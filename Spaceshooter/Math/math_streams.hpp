#ifndef MATH_STREAMS_HPP
#define MATH_STREAMS_HPP

#include "../Math/vec3.hpp"

#include <iostream>

namespace math {

  std::ostream& operator<< (std::ostream& stream, const vec3& v) {
    stream << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return stream;
  }
}


#endif
