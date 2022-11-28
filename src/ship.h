// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "hitbox.h"
#include "objectman.h"

#include "clksheet.h"

#include <bitset>
#include <list>
#include <memory>

struct ship;
class objectman;

// namespace clk {
// class sheet;
// }

class controller {
public:
  controller(objectman &);
  virtual void push(idpair ship);
  virtual void damaged(ship &source, const ship &target);
  virtual void destroyed(ship &source);
  virtual void colliding(ship &source, const ship &target);
  virtual void despawned(idpair source);

protected:
  objectman &objman;
  std::list<idpair> ships;
};

struct ship {
public:
  ship &initship(double x, double y, int hp, std::vector<hitbox> *boxes,
                 std::shared_ptr<clk::sheet> sheet, int id, controller *ai, double deltax, double deltay, double rotation);

  idpair objectid;
  std::bitset<1> objflags = 0;

  double x;
  double y;
  double rotation = 0;

  double deltax = 0;
  double deltay = 0;

  std::vector<hitbox> *boxes;

  std::shared_ptr<clk::sheet> sheet;
  int sheetid, frame;

  controller *ai;

  int hp;

  inline void draw() { sheet->drawframe(vports::CENTER, sheetid, frame, x, y); }
};
