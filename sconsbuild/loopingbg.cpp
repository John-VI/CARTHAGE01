// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "loopingbg.h"

#include "clktex.h"

#include <SDL2/SDL.h>

#define CORRECTAXIS (offsetxaxis ? bg.getw() : bg.geth())
#define ADJUSTEDANGLE fmod(travelangle + angle, 360)

double loopingbg::tick(double ticks) {
  position += ticks * rate;

  if (position >= abs(length) || position <= -abs(length)) {
    currentoffset += offsetxaxis ? position * SDL_cos(deg2rad(travelangle))
                                 : position * SDL_sin(deg2rad(travelangle));
    if (abs(currentoffset) >= abs(CORRECTAXIS))
      currentoffset = currentoffset >= 0 ? currentoffset - CORRECTAXIS
                                         : currentoffset + CORRECTAXIS;
    position = position >= 0 ? position - abs(length) : position + abs(length);
  }

  return position;
}

void loopingbg::updatepathing() {
  double critangle = rad2deg(SDL_atan2(bg.geth(), bg.getw()));

  if (travelangle >= 360 - critangle || travelangle < critangle) {
    length = bg.getw() / SDL_cos(deg2rad(travelangle));
    offsetxaxis = false;
  } else if (travelangle >= critangle && travelangle < 180 - critangle) {
    length = bg.geth() / SDL_sin(deg2rad(travelangle));
    offsetxaxis = true;
  } else if (travelangle >= 180 - critangle && travelangle < 180 + critangle) {
    length = bg.getw() / SDL_cos(deg2rad(travelangle));
    offsetxaxis = false;
  } else if (travelangle >= 180 + critangle && travelangle < 360 - critangle) {
    length = bg.geth() / SDL_sin(deg2rad(travelangle));
    offsetxaxis = true;
  }

  position = 0;
  currentoffset = 0;

  // TODO: Split this part off into new function(s) to update drawing. This
  // should just be pathing.

  upright = rotpoint(bg.getw(), 0, deg2rad(angle));
  downleft = rotpoint(0, bg.geth(), deg2rad(angle));
}

void loopingbg::drawone(double x, double y) {
  bg.draw(vports::FULL,
          position * SDL_cos(deg2rad(travelangle + angle)) + x * upright.x +
              y * downleft.x +
              (offsetxaxis ? rotpoint(currentoffset, 0, deg2rad(angle)).x
                           : rotpoint(0, currentoffset, deg2rad(angle)).x),
          position * SDL_sin(deg2rad(travelangle + angle)) + y * downleft.y +
              x * upright.y +
              (offsetxaxis ? rotpoint(currentoffset, 0, deg2rad(angle)).y
                           : rotpoint(0, currentoffset, deg2rad(angle)).y),
          angle);
}

void loopingbg::draw() {
  for (int i = -10; i <= 10; i++)
    for (int j = -10; j <= 10; j++)
      drawone(i, j);

  // std::cout << position * SDL_cos(deg2rad(travelangle)) << std::endl
  //           << position * SDL_sin(deg2rad(travelangle)) << std::endl
  //           << length << std::endl
  //           << position << std::endl;
}

loopingbg::loopingbg(clk::sprite &bg) : bg(bg) { updatepathing(); }
