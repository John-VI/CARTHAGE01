// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "objectman.h"

#include "hitbox.h"
#include "ship.h"

#include "clkwin.h"
#include "clksheet.h"

#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

void objectman::indexman::init(size_t preallocsize) {
  for (shipindex i = 0; i < preallocsize; i++) {
    objects.push_back(ship());
    objects.back().objectid.index = i;
  }

  for (shipindex i = 0; i < preallocsize; i++)
    deadindices.push_back(i);

  liveindices.reserve(preallocsize);
}

objectman::objectman(hitbox field) : field(field) {
  objects[(int)shiptype::PLAYER].init(2);

  for (int i = 1; i < (int)shiptype::MAX; i++)
    objects[i].init(preallocsize);
}

inline void objectman::indexman::enableship(shiptype t, shipindex i, double x,
                                            double y, int hp,
                                            std::vector<hitbox> *boxes,
                                            std::shared_ptr<clk::sheet> sheet,
                                            int id, controller *ai, double dx, double dy, double rot) {
  objects[i].initship(x, y, hp, boxes, sheet, id, ai, dx, dy, rot);
  objects[i].objectid.type = t;
  objects[i].objectid.id++;
  objects[i].objflags[0] = true;

  if (ai)
    objects[i].ai->push({t, i, objects[i].objectid.id});
}

inline void objectman::enableship(shiptype type, shipindex index, double x,
                                  double y, int hp, std::vector<hitbox> *boxes,
                                  std::shared_ptr<clk::sheet> sheet, int id,
                                  controller *ai, double dx, double dy, double rot) {
  objects[(int)type].enableship(type, index, x, y, hp, boxes, sheet, id, ai, dx, dy, rot);
}

inline idpair objectman::indexman::newobject(shiptype t, double x, double y,
                                             int hp, std::vector<hitbox> *boxes,
                                             std::shared_ptr<clk::sheet> sheet,
                                             int id, controller *ai, double deltax, double deltay, double rotation) {

  if (deadindices.empty()) {
    liveindices.push_back(objects.size());
    objects.push_back(ship());
  } else {
    liveindices.push_back(deadindices.back());
    deadindices.pop_back();
  }

  enableship(t, liveindices.back(), x, y, hp, boxes, sheet, id, ai, deltax, deltay, rotation);
  return {t, liveindices.back(), objects.back().objectid.id};
}

idpair objectman::newobject(shiptype t, double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai, double dx, double dy, double rot) {
  return objects[(int)t].newobject(t, x, y, hp, boxes, sheet, id, ai, dx, dy, rot);
}

ship *objectman::operator[](idpair i) {
  indexman &iman = objects[(int)i.type];
  if (iman.objects.at(i.index).objectid.id == i.id &&
      iman.objects[i.index].objflags[0])
    return &iman.objects[i.index];
  else
    return nullptr;
}

inline void objectman::indexman::delobject(idpair i, ship *s) {
  deadindices.push_back(s->objectid.index);

  auto t = std::find(liveindices.begin(), liveindices.end(), s->objectid.index);
  if (t != liveindices.end()) {
    std::swap(*t, liveindices.back());
    liveindices.pop_back();
  }
}

void objectman::delobject(idpair i) {
  ship *s = (*this)[i];
  if (s) {
    if (s->ai) {
    s->ai->despawned(i);
    s->ai = nullptr;
    }
    s->objflags[0] = false;

    objects[(int)i.type].delobject(i, s);
  }
}

void objectman::tick(Uint32 step) {
  for (auto &i : objects) {
    for (int j = 0; j < i.liveindices.size(); j++) { // We're using the dimensions of the center field in the rendering
                                       // temporarily. Soon I'll decouple this.
      auto &t = i.objects[i.liveindices[j]];
      t.x += t.deltax * step;
      t.y += t.deltay * step;

      hitbox space = hitbox(static_cast<SDL_Rect>(t.sheet->getframe(t.sheetid)));
      space.x += t.x;
      space.y += t.y;

      if (!field.colliding(space)) { // I cannot wake up from this nightmare
        delobject(t.objectid);
        j--;
      }
    }
  }
}

void objectman::draw() {
  for (auto &i : objects)
    for (auto &t : i.liveindices)
      i.objects[t].draw();
}
