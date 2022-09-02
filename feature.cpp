// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "feature.h"

#include "tile.h"

feature::feature(tile &t) : t(t) {}
void feature::step(monster &) {}
void feature::hit(monster &) {}
void feature::act(monster &) {}
void feature::tick() {}
