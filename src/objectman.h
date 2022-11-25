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

typedef std::vector<ship>::size_type shipindex;

struct idpair {
  shipindex index;
  int id;

  inline bool operator==(const idpair &other) const {
    return other.index == index && other.id == id;
  }
};

class objectman {
public:
  objectman();

  ship *operator[](idpair);
  idpair newobject(double x, double y, int hp, std::vector<hitbox> *boxes,
                   std::shared_ptr<clk::sheet> sheet, int id, controller *ai);
  void delobject(idpair);

  void tick(Uint32 step);
  void draw();

protected:
  const static std::size_t preallocsize = 128;

  std::vector<ship> objects;
  std::vector<shipindex> liveindices;
  std::vector<shipindex> deadindices;

  inline void enableship(unsigned long long index, double x, double y, int hp,
                         std::vector<hitbox> *boxes,
                         std::shared_ptr<clk::sheet> sheet, int id,
                         controller *ai);
};
