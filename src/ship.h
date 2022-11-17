// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "hitbox.h"

#include <memory>
#include <functional>
#include <vector>
#include <list>
#include <bitset>

class ship;

namespace clk {
  class sheet;
}

struct controller {
  controller(ship *);
  virtual void damaged(ship &source, const ship &target);
  virtual void destroyed(ship &source);
  virtual void colliding(ship &source, const ship &target);
  virtual void created(ship &source);

  ship *target;
};

struct ship {
public:
  ship(double x, double y, int hp, std::vector<hitbox> boxes, std::shared_ptr<clk::sheet> sheet, int id, controller *ai);
  ~ship();

  double x;
  double y;

  double deltax = 0;
  double deltay = 0;

  std::vector<hitbox> boxes;

  std::shared_ptr<clk::sheet> sheet;
  int id, frame;

  controller *ai;

  int hp;

  void tick(double ticks);
  void draw();

  int objectid;
  std::bitset<1> objflags;
};
