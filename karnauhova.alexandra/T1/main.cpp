#include <string>
#include <iostream>
#include "input.hpp"
#include "output.hpp"
#include "shape.hpp"
#include "check.hpp"
int main()
{
  if (
  if (names[0] == "SCALE" || names[0].empty())
  {
    std::cerr << "Error: empty input\n";
    return 1;
  }
  if (names[count_shape-1] != "SCALE")
  {
    std::cerr << "Error: missing scale\n";
    return 1;
  }
  if (points[i - 1] < 0)
  {
    std::cerr << "Error: missing scale\n";
    return 1;
  }
  if (count_error > 0)
  {
    std::cerr << "Error in the input\n";
  }
  karnauhova::output(std::cout, points, polygon, names, i, count_shape);
}
