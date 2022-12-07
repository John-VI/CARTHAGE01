// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "objectman.h"

#include "hitbox.h"
#include "ship.h"

#include "clksheet.h"
#include "clkviewport.h"
#include "clkwin.h"

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
                                            int id, controller *ai, double dx,
                                            double dy, double rot) {
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
                                  controller *ai, double dx, double dy,
                                  double rot) {
  objects[(int)type].enableship(type, index, x, y, hp, boxes, sheet, id, ai, dx,
                                dy, rot);
}

inline idpair objectman::indexman::newobject(shiptype t, double x, double y,
                                             int hp, std::vector<hitbox> *boxes,
                                             std::shared_ptr<clk::sheet> sheet,
                                             int id, controller *ai,
                                             double deltax, double deltay,
                                             double rotation) {

  if (deadindices.empty()) {
    liveindices.push_back(objects.size());
    objects.push_back(ship());
  } else {
    liveindices.push_back(deadindices.back());
    deadindices.pop_back();
  }

  enableship(t, liveindices.back(), x, y, hp, boxes, sheet, id, ai, deltax,
             deltay, rotation);
  return {t, liveindices.back(), objects.back().objectid.id};
}

idpair objectman::newobject(shiptype t, double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai, double dx, double dy, double rot) {
  return objects[(int)t].newobject(t, x, y, hp, boxes, sheet, id, ai, dx, dy,
                                   rot);
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

inline hitbox tickship(ship &t, Uint32 step) {
  t.x += t.deltax * step;
  t.y += t.deltay * step;

  hitbox space = hitbox(static_cast<SDL_Rect>(t.sheet->getframe(t.sheetid)));
  space.x += t.x;
  space.y += t.y;

  return space;
}

void objectman::tick(Uint32 step) {
  // for (int j = 0; j < objects[(int)shiptype::PLAYER].liveindices.size(); j++)
  // { // We're using the dimensions of the center field in the rendering
  //   // temporarily. Soon I'll decouple this.
  //   auto &i = objects[(int)shiptype::PLAYER];
  //   auto space = tickship(i.objects[i.liveindices[j]], step);

  //   if (!field.colliding(space)) { // I cannot wake up from this nightmare
  //     delobject(i.objects[i.liveindices[j]].objectid);
  //     j--;
  //   } else {

  //   }
  // }

  for (auto &i : objects) {
    for (int j = 0; j < i.liveindices.size(); j++) {
      auto space = tickship(i.objects[i.liveindices[j]], step);

      if (!field.colliding(space)) { // I cannot wake up from this nightmare
        delobject(i.objects[i.liveindices[j]].objectid);
        j--;
      }
    }
  }
}

int objectman::drawboxes(const ship &s, clk::viewport port) {
  const clk::frameinfo &frame = s.sheet->getframe(s.sheetid);
  SDL_Rect destination{port.x + (int)s.x - frame.w / 2,
                       port.y + (int)s.y - frame.h / 2, frame.w, frame.h};

  s.sheet->drawrect(&destination, {0, 0, 255});

  for (const auto &t : *s.boxes) {
    SDL_Rect destination{port.x + (int)s.x - t.w / 2 + t.x,
                         port.y + (int)s.y - t.h / 2 + t.y, t.w, t.h};
    s.sheet->drawrect(&destination, {255, 0, 0});
  }
  return 0;
}

void objectman::draw(clk::viewport port) {
  for (auto &i : draworder)
    for (auto &t : objects[i].liveindices) {
      objects[i].objects[t].draw();
      drawboxes(objects[i].objects[t], port);
    }
}
