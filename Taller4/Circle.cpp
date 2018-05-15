#include "Circle.h"

Circle::Circle(float _R) {
  this->R = _R;
}

Point Circle::getPoint(float t) {
  Point p(this->R*cos(t), this->R*sin(t), 0.0);
  return p;
}

void Circle::print() {
  std::cout << "R: " << this->R << std::endl;
}
