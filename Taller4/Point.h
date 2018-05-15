#ifndef _POINT_H
#define _POINT_H

#include <iostream>

struct Point {
  float x, y, z;
  
  Point(float _x, float _y, float _z);
  void print();
};

#endif
