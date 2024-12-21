#ifndef PARALLELOGRAM_HPP
#define PARALLELOGRAM_HPP
#include "shape.hpp"
namespace bocharov
{
  class Parallelogram : public Shape {
    point_t pos_;
    point_t p1_;
    point_t p2_;

   public:
    Parallelogram();
    Parallelogram(const point_t& p1, const point_t& p2, const point_t& p3);
    double getArea() const  override;
    rectangle_t getFrameRect() const override;
    void move(point_t p) override;
    void move(double dx, double dy) override;
    void scale(double k) override;
  };
}
#endif
