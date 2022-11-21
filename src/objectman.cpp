// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "objectman.h"

#include "hitbox.h"
#include "ship.h"

#include <memory>
#include <vector>

#include <iostream>

bool idpair::operator==(const idpair &other) const {
  return other.index == index && other.id == id;
}

objectman::objectman() { objects.reserve(64); }

inline void objectman::enableship(unsigned long long i, double x, double y, int hp,
                           std::vector<hitbox> *boxes,
                           std::shared_ptr<clk::sheet> sheet, int id,
                           controller *ai) {
  objects[i].initship(x, y, hp, boxes, sheet, id, ai);
  objects[i].objectid++;
  objects[i].objflags[0] = true;
  objects[i].ai->push({i, objects[i].objectid});
}

idpair objectman::newobject(double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai) {
  for (unsigned long long i = 0; i < objects.size(); i++)
    if (!objects[i].objflags[0]) {
      enableship(i, x, y, hp, boxes, sheet, id, ai);

      return {i, objects[i].objectid};
    }

  objects.push_back(ship());
  enableship(objects.size() - 1, x, y, hp, boxes, sheet, id, ai);
  return {objects.size() - 1, objects.back().objectid};
}

ship *objectman::operator[](idpair i) {
  if (objects.at(i.index).objectid == i.id && objects[i.index].objflags[0])
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
  }
}

void objectman::tick(Uint32 step) {
  for (auto &t : objects)
    if (t.objflags[0])
      t.tick(step);
}

void objectman::draw() {
  for (auto &t: objects)
    if (t.objflags[0])
      t.draw();
}
