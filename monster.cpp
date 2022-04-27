// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "monster.h"

#include <string>

#include "clktex.h"

#include "grid.h"

monster::monster(const int type, const char family,
		 std::string name) : type(type), family(family),
				     name(name) { }

int monster::tick() {
  meter -= speed;
  if (meter <= 0) {
    ai();
    meter += 100;
  }
  return meter;
}

void monster::draw() {
  g->font.drawchar(x * g->w, y * g->h, family);
}

