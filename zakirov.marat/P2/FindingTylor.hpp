#ifndef FINDINGTYLOR_HPP
#define FINDINGTYLOR_HPP
#include <cstddef>
#include <stdexcept>
#include <cmath>

namespace zakirov
{
  double find_atanh(double point, size_t addition_depth, const double kError);
  double get_atanh(double point);
}

#endif
