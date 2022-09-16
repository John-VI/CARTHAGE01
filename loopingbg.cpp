// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "loopingbg.h"

#include "clktex.h"

#include <SDL2/SDL.h>

#include <iostream>

#define correctaxis (offsetxaxis ? bg.getw() : bg.geth())

double loopingbg::tick(double ticks) {
  position += ticks * rate;

  if (position >= abs(length) || position <= -abs(length)) {
    currentoffset += offsetxaxis ? position * SDL_cos(deg2rad(travelangle)) : position * SDL_sin(deg2rad(travelangle));
    if (abs(currentoffset) >= abs(offsetxaxis ? bg.getw() : bg.geth()))
      currentoffset = currentoffset >= 0 ? currentoffset - correctaxis : currentoffset + correctaxis;
    position = position >= 0 ? position - abs(length) : position + abs(length);
    std::cout << currentoffset << std::endl << offsetxaxis << std::endl;
  }

  return position;
}

void loopingbg::updatepathing() {
  double critangle = rad2deg(SDL_atan2(bg.geth(), bg.getw()));

  if (travelangle <= 360 - critangle && travelangle < critangle) {
    length = bg.getw() / SDL_cos(deg2rad(travelangle));
    offsetxaxis = false;
  }
  else if (travelangle >= critangle && travelangle < 180 - critangle) {
    length = bg.geth() / SDL_sin(deg2rad(travelangle));
    offsetxaxis = true;
  }
  else if (travelangle >= 180 - critangle && travelangle < 180 + critangle) {
    length = bg.getw() / SDL_cos(deg2rad(travelangle));
    offsetxaxis = false;
  }
  else if (travelangle >= 180 + critangle && travelangle < 360 - critangle) {
    length = bg.geth() / SDL_sin(deg2rad(travelangle));
    offsetxaxis = true;
  }

  std::cout << "Critical angle: " << critangle << std::endl;

  position = 0;
  currentoffset = 0;
}

void loopingbg::drawone(double x, double y) {
  bg.draw(vports::FULL, position * SDL_cos(deg2rad(travelangle)) + x + (offsetxaxis ? currentoffset : 0),
          position * SDL_sin(deg2rad(travelangle)) + y + (offsetxaxis ? 0 : currentoffset));
}

void loopingbg::draw() {
  for (int i = -2; i <= 2; i++)
    for (int j = -2; j <= 2; j++)
      drawone(bg.getw() * i, bg.geth() * j);

  // std::cout << position * SDL_cos(deg2rad(travelangle)) << std::endl
  //           << position * SDL_sin(deg2rad(travelangle)) << std::endl
  //           << length << std::endl
  //           << position << std::endl;
}

loopingbg::loopingbg(clk::sprite &bg) : bg(bg) {
  updatepathing();
}
