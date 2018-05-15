#include "Point.h"

Point::Point(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

void Point::print() {
  std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}
