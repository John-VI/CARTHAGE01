// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "door.h"

#include "feature.h"
#include "monster.h"
#include "tileflag.h"

const tflags door::closedflags = (TILEFLAG_UNDERLYING)tileflag::DESTRUCT;
const tflags door::openflags = (char)(tileflag::PASSABLE | tileflag::TRANSLUC);


door::door(tile &t) : feature(t) {
  open = open % 2;
  fflags = 1;
  toggle();
}

void door::toggle() {
  if (open) {
    open = false;
    sprite = '8';
  } else {
    open = true;
    sprite = '0';
  }
}

void door::act(monster &) { toggle(); }

tflags door::flags() {
  return open ? openflags : closedflags;
}
