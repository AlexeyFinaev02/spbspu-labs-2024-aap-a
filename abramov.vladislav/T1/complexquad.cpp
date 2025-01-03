#include "complexquad.hpp"
#include <stdexcept>
#include <cmath>
#include <limits>

namespace abramov
{
  void searchInArray(double *x, double &a, double &b, size_t k)
  {
    double max = std::numeric_limits< double >::min();
    double min = std::numeric_limits< double >::max();
    for (size_t i = 0; i < k; ++i)
    {
      if (x[i] > max)
      {
        max = x[i];
      }
      if (x[i] < min)
      {
        min = x[i];
      }
    }
    a = min;
    b = max;
  }

  void getCoordsOfIntersection (point_t A, point_t B, point_t C, point_t D, double &x, double &y)
  {
    const double k1 = (B.y - A.y) / (B.x - A.x);
    const double b1 = A.y - A.x * k1;
    const double k2 = (D.y - C.y) / (D.x - C.x);
    const double b2 = C.y - C.x * k2;
    if (k1 == k2)
    {
      throw std::logic_error("There is no center\n");
    }
    x = (b2 - b1) / (k1 - k2);
    y = k1 * x + b1;
    if (x == A.x || x == B.x || x == C.x || x == D.x)
    {
      throw std::logic_error("There is no center\n");
    }
    constexpr size_t k = 4;
    double xs[k] = {A.x, B.x, C.x, D.x};
    size_t count = 0;
    for (size_t i = 0; i < k; ++i)
    {
      if (x > xs[i])
      {
        ++count;
      }
    }
    if (count != 2)
    {
      throw std::logic_error("There is no center\n");
    }
  }

  double getTriangleArea(point_t A, point_t B, point_t O)
  {
    const double a = getLength(A, B);
    const double b = getLength(B, O);
    const double c = getLength(O, A);
    const double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
  }

  ComplexQuad::ComplexQuad(point_t A, point_t B, point_t C, point_t D):
   A_(A),
   B_(B),
   C_(C),
   D_(D)
  {
    try
    {
      double x = 0;
      double y = 0;
      getCoordsOfIntersection(A, B, C, D, x, y);
    }
    catch (const std::logic_error &e)
    {
      throw std::logic_error("It is impossible to build ComplexQuad\n");
    }
  }

  double ComplexQuad::getArea() const
  {
    const point_t center = getCenterComplexQuad();
    return getTriangleArea(A_, D_, center) + getTriangleArea(B_, C_, center);
  }

  rectangle_t ComplexQuad::getFrameRect() const
  {
    constexpr size_t k = 4;
    double x[k] = {A_.x, B_.x, C_.x, D_.x};
    double y[k] = {A_.y, B_.y, C_.y, D_.y};
    double max_x = 0;
    double min_x = 0;
    double max_y = 0;
    double min_y = 0;
    searchInArray(x, min_x, max_x, k);
    searchInArray(y, min_y, max_y, k);
    rectangle_t frame_rect;
    frame_rect.width = max_x - min_x;
    frame_rect.height = max_y - min_y;
    point_t pos;
    pos.x = (max_x + min_x) / 2;
    pos.y = (max_y + min_y) / 2;
    frame_rect.pos = pos;
    return frame_rect;
  }

  point_t ComplexQuad::getCenterComplexQuad() const
  {
    double x = 0;
    double y = 0;
    point_t center;
    getCoordsOfIntersection(A_, B_, C_, D_, x, y);
    center.x = x;
    center.y = y;
    return center;
  }

  void ComplexQuad::move(point_t p)
  {
    const point_t center = getCenterComplexQuad();
    const double dx = p.x - center.x;
    const double dy = p.y - center.y;
    move(dx, dy);
  }

  void ComplexQuad::move(double dx, double dy)
  {
    A_.x += dx;
    B_.x += dx;
    C_.x += dx;
    D_.x += dx;
    A_.y += dy;
    B_.y += dy;
    C_.y += dy;
    D_.y += dy;
  }

  void ComplexQuad::scale(double k)
  {
    const point_t O = getCenterComplexQuad();
    const double dk = k - 1;
    A_.x -= (O.x - A_.x) * dk;
    A_.y -= (O.y - A_.y) * dk;
    B_.x -= (O.x - B_.x) * dk;
    B_.y -= (O.y - B_.y) * dk;
    C_.x -= (O.x - C_.x) * dk;
    C_.y -= (O.y - C_.y) * dk;
    D_.x -= (O.x - D_.x) * dk;
    D_.y -= (O.y - D_.y) * dk;
  }

  point_t ComplexQuad::getA() const
  {
    return A_;
  }

  point_t ComplexQuad::getB() const
  {
    return B_;
  }

  point_t ComplexQuad::getC() const
  {
    return C_;
  }

  point_t ComplexQuad::getD() const
  {
    return D_;
  }
}
