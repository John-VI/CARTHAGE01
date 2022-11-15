// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "hitbox.h"

#include <memory>
#include <functional>
#include <vector>

class ship;

namespace clk {
  class sheet;
}

struct controller {
  virtual void damaged(ship &source, const ship &target);
  virtual void destroyed(ship &source);
  virtual void colliding(ship &source, const ship &target);
  virtual void created(ship &source);
};

struct ship {
public:
  ship(int x, int y, int hp, std::vector<hitbox> boxes, std::shared_ptr<clk::sheet> sheet, int id, controller &ai);
  ~ship();

  int x;
  int y;

  std::vector<hitbox> boxes;

  double speed = 0;
  double heading = 0; // Angle expressed in radians.

  std::shared_ptr<clk::sheet> sheet;
  int id, frame;

  controller &ai;

  int hp;

  void tick(double ticks);
  void draw();
};
