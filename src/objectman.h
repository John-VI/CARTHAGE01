// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <array>
#include <memory>
#include <vector>

#include "hitbox.h"

struct ship;
struct controller;

namespace clk {
struct sheet;
}

typedef std::vector<ship>::size_type shipindex;

enum class shiptype { PLAYER, ENEMY, PBULLET, EBULLET, MAX };

struct idpair {
  shiptype type;
  shipindex index;
  int id;

  inline bool operator==(const idpair &other) const {
    return other.index == index && other.id == id && other.type == type;
  }
};

class objectman {
public:
  objectman(hitbox field);

  ship *operator[](idpair);
  idpair newobject(shiptype t, double x, double y, int hp,
                   std::vector<hitbox> *boxes,
                   std::shared_ptr<clk::sheet> sheet, int id,
                   controller *ai = nullptr, double deltax = 0,
                   double deltay = 0, double rotation = 0);
  void delobject(idpair);

  void tick(Uint32 step);
  void draw();

  const hitbox field;

protected:
  struct indexman {
    std::vector<ship> objects;
    std::vector<shipindex> liveindices;
    std::vector<shipindex> deadindices;

    void init(size_t preallocsize);
    inline idpair newobject(shiptype type, double x, double y, int hp,
                            std::vector<hitbox> *boxes,
                            std::shared_ptr<clk::sheet> sheet, int id,
                            controller *ai = nullptr, double deltax = 0,
                            double deltay = 0, double rotation = 0);
    inline void enableship(shiptype type, shipindex index, double x, double y,
                           int hp, std::vector<hitbox> *boxes,
                           std::shared_ptr<clk::sheet> sheet, int id,
                           controller *ai,
                           double deltax, double deltay, double rotation);
    inline void delobject(idpair, ship *);
  };

  static const size_t preallocsize = 128;

  std::array<indexman, (int)shiptype::MAX> objects;

  inline void enableship(shiptype type, shipindex index, double x, double y,
                         int hp, std::vector<hitbox> *boxes,
                         std::shared_ptr<clk::sheet> sheet, int id,
                         controller *ai, double deltax, double deltay, double rotation);
};
