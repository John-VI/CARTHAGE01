// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "ship.h"

#include "hitbox.h"
#include "objectman.h"

#include "clksheet.h"

#include <SDL2/SDL.h>

#include <functional>
#include <memory>
#include <vector>

#include <iostream>

// ship::ship(double x, double y, int hp, std::vector<hitbox> *boxes,
//            std::shared_ptr<clk::sheet> sheet, int id, controller *ai)
//     : x(x), y(y), boxes(boxes), sheet(sheet), id(id), frame(0), ai(ai),
//     hp(hp) {
//   ai->created(*this);
// }

controller::controller(objectman &man) : objman(man) {}

ship &ship::initship(double x, double y, int hp, std::vector<hitbox> *boxes,
                     std::shared_ptr<clk::sheet> sheet, int id,
                     controller *ai, double dx, double dy, double rot) {
  this->x = x;
  this->y = y;
  this->hp = hp;
  this->boxes = boxes;
  this->sheet = sheet;
  this->sheetid = id;
  this->frame = 0;
  this->ai = ai;
  this->deltax = dx;
  this->deltay = dy;
  this->rotation = rot;

  return *this;
}

void controller::damaged(ship &source, const ship &target) {}
void controller::destroyed(ship &source) {}
void controller::colliding(ship &source, const ship &target) {}

void controller::push(idpair ship) { ships.push_back(ship); }

void controller::despawned(idpair source) { ships.remove(source); }

void controller::tick(uint32_t) { return; }
