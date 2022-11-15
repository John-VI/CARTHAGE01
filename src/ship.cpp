// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "ship.h"

#include "hitbox.h"

#include "clksheet.h"

#include <SDL2/SDL.h>

#include <functional>
#include <memory>
#include <vector>

ship::ship(int x, int y, int hp, std::vector<hitbox> boxes,
           std::shared_ptr<clk::sheet> sheet, int id, controller &ai)
    : x(x), y(y), hp(hp), boxes(boxes), sheet(sheet), id(id), ai(ai), frame(0) {
  ai.created(*this);
}

ship::~ship() {
  ai.destroyed(*this);
}

void ship::tick(double ticks) {
  x += speed * SDL_cos(heading) * ticks;
  y += speed * SDL_sin(heading) * ticks;
}

void ship::draw() {
  sheet->drawframe(vports::CENTER, id, frame, x, y);
}
