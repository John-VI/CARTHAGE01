// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "door.h"

#include "feature.h"
#include "monster.h"

door::door(tile &t) : feature(t) {
  custflags = true;
  open = open % 2;
  fflags = 1;
  toggle();
}

void door::toggle() {
  if (open) {
    open = false;
    flags = closedflags;
    sprite = '8';
  } else {
    open = true;
    flags = openflags;
    sprite = '0';
  }
}

void door::act(monster &) { toggle(); }
