// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <SDL2/SDL.h>

namespace clk {
typedef struct sprite sprite;
}

class loopingbg {
 protected:
  clk::sprite &bg;
  double position = 0;

 public:
   double angle = 0;
   double travelangle = 0;
   double rate = 0;
   int offset = 0;
};
