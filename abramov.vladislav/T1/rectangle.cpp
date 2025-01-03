#include "rectangle.hpp"
#include <stdexcept>
#include <algorithm>
#include "shape.hpp"
#include "base-types.hpp"

namespace abramov
{
  Rectangle::Rectangle(point_t p1, point_t p2):
   cmplxqd1_({p1.x, p1.y}, {(p1.x + p2.x) / 2, p2.y}, {(p1.x + p2.x) / 2, p1.y}, {p1.x, p2.y}),
   cmplxqd2_({p1.x, p2.y}, {(p1.x + p2.x) / 2, p1.y}, {p1.x, p1.y}, {(p1.x + p2.x) / 2, p2.y}),
   cmplxqd3_({(p1.x + p2.x) / 2, p1.y}, {p2.x, p2.y}, {p2.x, p1.y}, {(p1.x + p2.x) / 2, p2.y}),
   cmplxqd4_({(p1.x + p2.x) / 2, p2.y}, {p2.x, p1.y}, {(p1.x + p2.x) / 2, p1.y}, {p2.x, p2.y})
  {
    if (p1.x >= p2.x || p1.y >= p2.y)
    {
      throw std::logic_error("Impossible to build a rectangle");
    }
    const double x1 = p1.x;
    const double y1 = p1.y;
    const double x2 = p2.x;
    const double y2 = p2.y;
    if (p2.x - p1.x >= p2.y - p1.y)
    {
      const double x3 = (x1 + x2) / 2;
      cmplxqd1_ = ComplexQuad({x1, y1}, {x3, y2}, {x3, y1}, {x1, y2});
      cmplxqd2_ = ComplexQuad({x1, y2}, {x3, y1}, {x1, y1}, {x3, y2});
      cmplxqd3_ = ComplexQuad({x3, y1}, {x2, y2}, {x2, y1}, {x3, y2});
      cmplxqd4_ = ComplexQuad({x3, y2}, {x2, y1}, {x3, y1}, {x2, y2});
    }
    else
    {
      const double y3 = (y1 + y2) / 2;
      cmplxqd1_ = ComplexQuad({x1, y2}, {x2, y3}, {x2, y2}, {x1, y3});
      cmplxqd2_ = ComplexQuad({x1, y3}, {x2, y2}, {x1, y2}, {x2, y3});
      cmplxqd3_ = ComplexQuad({x1, y1}, {x2, y3}, {x2, y1}, {x1, y3});
      cmplxqd4_ = ComplexQuad({x1, y1}, {x2, y3}, {x1, y3}, {x2, y1});
    }
  }

  double Rectangle::getArea() const
  {
    return cmplxqd1_.getArea() + cmplxqd2_.getArea() + cmplxqd3_.getArea() + cmplxqd4_.getArea();
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    const double width = cmplxqd4_.getD().x - cmplxqd1_.getA().x;
    double height = std::abs(cmplxqd4_.getD().y - cmplxqd1_.getA().y);
    if (height == 0)
    {
      height = cmplxqd1_.getB().y - cmplxqd1_.getA().y;
    }
    point_t pos;
    pos.x = (cmplxqd1_.getA().x + cmplxqd4_.getD().x) / 2;
    pos.y = (cmplxqd1_.getA().y + cmplxqd4_.getD().y) / 2;
    rectangle_t frame_rect{width, height, pos};
    return frame_rect;
  }

  void Rectangle::move(double dx, double dy)
  {
    cmplxqd1_.move(dx, dy);
    cmplxqd2_.move(dx, dy);
    cmplxqd3_.move(dx, dy);
    cmplxqd4_.move(dx, dy);
  }

  void Rectangle::move(point_t p)
  {
    const point_t center = getFrameRect().pos;
    const double dx = p.x - center.x;
    const double dy = p.y - center.y;
    move(dx, dy);
  }

  void Rectangle::scale(double k)
  {
    const double newWidth = (cmplxqd4_.getD().x - cmplxqd1_.getA().x) * k;
    double height = 0;
    const double dy = std::abs(cmplxqd4_.getD().y - cmplxqd1_.getA().y);
    if (dy == 0)
    {
      height = cmplxqd1_.getB().y - cmplxqd1_.getA().y;
    }
    else
    {
      height = dy;
    }
    const double newHeight = height * k;
    const point_t center = getFrameRect().pos;
    const double x2 = center.x + newWidth / 2;
    const double y2 = center.y + newHeight / 2;
    const double x1 = center.x - newWidth / 2;
    const double y1 = center.y - newHeight / 2;
    if (x2 - x1 >= y2 - y1)
    {
      const double x3 = (x1 + x2) / 2;
      cmplxqd1_ = ComplexQuad({x1, y1}, {x3, y2}, {x3, y1}, {x1, y2});
      cmplxqd2_ = ComplexQuad({x1, y2}, {x3, y1}, {x1, y1}, {x3, y2});
      cmplxqd3_ = ComplexQuad({x3, y1}, {x2, y2}, {x2, y1}, {x3, y2});
      cmplxqd4_ = ComplexQuad({x3, y2}, {x2, y1}, {x3, y1}, {x2, y2});
    }
    else
    {
      const double y3 = (y1 + y2) / 2;
      cmplxqd1_ = ComplexQuad({x1, y2}, {x2, y3}, {x2, y2}, {x1, y3});
      cmplxqd2_ = ComplexQuad({x1, y3}, {x2, y2}, {x1, y2}, {x2, y3});
      cmplxqd3_ = ComplexQuad({x1, y1}, {x2, y3}, {x2, y1}, {x1, y3});
      cmplxqd4_ = ComplexQuad({x1, y1}, {x2, y3}, {x1, y3}, {x2, y1});
    }
  }
}
