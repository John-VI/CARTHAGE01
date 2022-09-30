// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <SDL2/SDL.h>

#include <numbers>

namespace clk {
typedef struct sprite sprite;
}

class loopingbg {
private:
  void inline drawone(double xoffset, double yoffset);
  SDL_Point upright;
  SDL_Point downleft;

protected:
  clk::sprite &bg;
  bool offsetxaxis;

public: // TODO: Change these to getters and setters to force updates on change.
  double angle = 0; // This angle runs counterclockwise and will be inverted for
                    // SDL's clockwise rendering.
  double travelangle = 0;
  double rate = 0;
  int offset = 0;

  loopingbg(clk::sprite &bg);

  double tick(double ticks);
  void draw();
  void updatepathing();

  double position = 0;
  double length;
  double currentoffset = 0;
};

// TODO: Move these to an official math helper header. Doing it after this
// commit to be atomic.

inline double deg2rad(double degrees) {
  return std::numbers::pi / 180 * degrees;
}

inline double rad2deg(double radians) {
  return radians * (180 / std::numbers::pi);
}

inline SDL_Point rotpoint(int x, int y, double radians) {
  return {static_cast<int>(x * SDL_cos(radians) - y * SDL_sin(radians)),
          static_cast<int>(x * SDL_sin(radians) + y * SDL_cos(radians))};
}

inline SDL_Point rotpoint(SDL_Point point, double radians) {
  return rotpoint(point.x, point.y, radians);
}
