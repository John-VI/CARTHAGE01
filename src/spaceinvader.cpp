// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "spaceinvader.h"

#include "ship.h"

using namespace ai;

spaceinvader::spaceinvader(objectman &objmanager) : controller(objmanager) { }

void spaceinvader::tick(uint32_t ticks) {
  bullettime += ticks;
  if (bullettime >= bulletthresh) {
    for (auto &t : ships) {
      auto s = objman[t];

      objman.newobject(shiptype::EBULLET, s->x , s->y, 1, s->boxes, s->sheet, 2, nullptr, 0, 0.5);
      s->deltax = -s->deltax;
    }
    bullettime -= bulletthresh;
  }
}
