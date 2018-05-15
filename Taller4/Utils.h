#ifndef __UTILS_H
#define __UTILS_H

#define SENTINEL "f"

#include "Point.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


class Utils {

  public:
    static void readPoints(const char *fileName, std::vector<Point> &p) {
      std::ifstream fileStream(fileName);
      std::string line;
      if(fileStream.is_open()) {
        float x, y;
        while(getline(fileStream, line) && line != SENTINEL) {
          std::cout << line << std::endl;
          std::stringstream ss(line);
           ss >> x; ss >> y;
           p.push_back(Point(x, y, 0.0));
        }
      }
    }

};

#endif
