#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace smirnov
{
  class Rectangle final: public Shape
  {
  public:
    Rectangle(double x1, double y1, double x2, double y2);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(point_t newPos) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  private:
    point_t lowerLeft;
    point_t upperRight;
  };
}
#endif
