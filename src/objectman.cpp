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
                                            int id, controller *ai) {
  objects[i].initship(x, y, hp, boxes, sheet, id, ai);
  objects[i].objectid.id++;
  objects[i].objflags[0] = true;
  objects[i].ai->push({t, i, objects[i].objectid.id});
}

inline void objectman::enableship(shiptype type, shipindex index, double x,
                                  double y, int hp, std::vector<hitbox> *boxes,
                                  std::shared_ptr<clk::sheet> sheet, int id,
                                  controller *ai) {
  objects[(int)type].enableship(type, index, x, y, hp, boxes, sheet, id, ai);
}

inline idpair objectman::indexman::newobject(shiptype t, double x, double y,
                                             int hp, std::vector<hitbox> *boxes,
                                             std::shared_ptr<clk::sheet> sheet,
                                             int id, controller *ai) {

  if (deadindices.empty()) {
    liveindices.push_back(objects.size());
    objects.push_back(ship());
  } else {
    liveindices.push_back(deadindices.back());
    deadindices.pop_back();
  }

  enableship(t, liveindices.back(), x, y, hp, boxes, sheet, id, ai);
  return {t, liveindices.back(), objects.back().objectid.id};
}

idpair objectman::newobject(shiptype t, double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai) {
  return objects[(int)t].newobject(t, x, y, hp, boxes, sheet, id, ai);
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
    s->ai->despawned(i);
    s->ai = nullptr;
    s->objflags[0] = false;

    objects[(int)i.type].delobject(i, s);
  }
}

void objectman::tick(Uint32 step) {
  for (auto &i : objects)
    for (auto &t : i.liveindices) { // We're using the dimensions of the center field in the rendering
                                    // temporarily. Soon I'll decouple this.
      i.objects[t].x += i.objects[t].deltax * step;
      i.objects[t].y += i.objects[t].deltay * step;

      hitbox space = hitbox(static_cast<SDL_Rect>(i.objects[t].sheet->getframe(i.objects[t].sheetid)));
      space.x += i.objects[t].x;
      space.y += i.objects[t].y;

    if (!field.colliding(space)) // I cannot wake up from this nightmare
        delobject(i.objects[t].objectid);
    }
}

void objectman::draw() {
  for (auto &i : objects)
    for (auto &t : i.liveindices)
      i.objects[t].draw();
}
