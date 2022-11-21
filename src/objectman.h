// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <memory>
#include <vector>

#include "hitbox.h"

struct ship;
struct controller;

namespace clk {
struct sheet;
}

struct idpair {
  unsigned long long index;
  int id;

  bool operator==(const idpair &other) const;
};

class objectman {
protected:
  std::vector<ship> objects;

  inline void enableship(unsigned long long index, double x, double y, int hp,
                  std::vector<hitbox> *boxes, std::shared_ptr<clk::sheet> sheet,
                  int id, controller *ai);

public:
  objectman();

  ship *operator[](idpair);
  idpair newobject(double x, double y, int hp, std::vector<hitbox> *boxes,
                   std::shared_ptr<clk::sheet> sheet, int id, controller *ai);
  void delobject(idpair);

  void tick(Uint32 step);
  void draw();
};
