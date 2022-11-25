// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "objectman.h"

#include "hitbox.h"
#include "ship.h"

#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>

objectman::objectman() {
  for (shipindex i = 0; i < preallocsize; i++) {
    objects.push_back(ship());
    objects.back().objectid.index = i;
  }

  for (shipindex i = 0; i < preallocsize; i++)
    deadindices.push_back(i);

  liveindices.reserve(preallocsize);
}

inline void objectman::enableship(unsigned long long i, double x, double y,
                                  int hp, std::vector<hitbox> *boxes,
                                  std::shared_ptr<clk::sheet> sheet, int id,
                                  controller *ai) {
  objects[i].initship(x, y, hp, boxes, sheet, id, ai);
  objects[i].objectid.id++;
  objects[i].objflags[0] = true;
  objects[i].ai->push({i, objects[i].objectid.id});
}

idpair objectman::newobject(double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai) {

  if (deadindices.empty()) {
    liveindices.push_back(objects.size());
    objects.push_back(ship());
  } else {
    liveindices.push_back(deadindices.back());
    deadindices.pop_back();
  }

  enableship(liveindices.back(), x, y, hp, boxes, sheet, id, ai);
  return {liveindices.back(), objects.back().objectid.id};
}

ship *objectman::operator[](idpair i) {
  if (objects.at(i.index).objectid.id == i.id && objects[i.index].objflags[0])
    return &objects[i.index];
  else
    return nullptr;
}

void objectman::delobject(idpair i) {
  ship *s = (*this)[i];
  if (s) {
    s->ai->despawned(i);
    s->ai = nullptr;
    s->objflags[0] = false;

    deadindices.push_back(s->objectid.index);

    auto t = std::find(liveindices.begin(), liveindices.end(), s->objectid.index);
    if (t != liveindices.end()) {
      std::swap(*t, liveindices.back());
      liveindices.pop_back();
    }
  }
}

void objectman::tick(Uint32 step) {
  for (auto &t : liveindices)
    objects[t].tick(step);
}

void objectman::draw() {
  for (auto &t : liveindices)
    objects[t].draw();
}
