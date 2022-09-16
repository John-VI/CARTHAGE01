// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <SDL2/SDL.h>

#include <numbers>

namespace clk {
typedef struct sprite sprite;
}

class loopingbg {
 protected:
  clk::sprite &bg;
  // double position = 0;
  // double length;
  // double currentoffset = 0;
  // bool offsetxaxis;
  void inline drawone(double xoffset, double yoffset);

 public:
   double angle = 0;
   double travelangle = 0;
   double rate = 0;
   int offset = 0;

   double position = 0;
   double length;
   double currentoffset = 0;
   bool offsetxaxis;

   loopingbg(clk::sprite &bg);

   double tick(double ticks);
   void draw();
   void updatepathing();
};

inline double deg2rad(double degrees) {
  return std::numbers::pi/180 * degrees;
}

inline double rad2deg(double radians) {
  return radians * (180 / std::numbers::pi);
}
