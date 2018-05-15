#ifndef __CIRCLE_H
#define __CIRCLE_H

#include <iostream>
#include <cmath>
#include "Point.h"

struct Circle {
  float R;

  Circle(float _R);
  Point getPoint(float t);
  void print();
};

#endif
