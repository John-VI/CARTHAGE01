// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "ship.h"

#include "hitbox.h"

#include "clksheet.h"

#include <SDL2/SDL.h>

#include <functional>
#include <memory>
#include <vector>

ship::ship(double x, double y, int hp, std::vector<hitbox> boxes,
           std::shared_ptr<clk::sheet> sheet, int id, controller *ai)
    : x(x), y(y), boxes(boxes), sheet(sheet), id(id), frame(0), ai(ai), hp(hp) {
  ai->created(*this);
}

ship::~ship() {
  ai->destroyed(*this);
}

void ship::tick(double ticks) {
  x += deltax * ticks;
  y += deltay * ticks;
}

void ship::draw() {
  sheet->drawframe(vports::CENTER, id, frame, x, y);
}

controller::controller(ship *t) : target(t) {}
void controller::damaged(ship &source, const ship &target) {}
void controller::destroyed(ship &source) {}
void controller::colliding(ship &source, const ship &target) {}
void controller::created(ship &source) {}
