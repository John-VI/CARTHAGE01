// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <list>
#include <memory>

#include "tile.h"
#include "monster.h"

namespace clk {
  typedef struct sprite sprite;
}

class grid {
  int w;
  int h;
  int twidth;
  int theight;
  std::list<std::unique_ptr<monster>> monsters;
  std::unique_ptr<tile[]> tiles;

 public:
  grid(int width, int height, int tilewidth, int tileheight, clk::sprite &font);

  clk::sprite &font;

  int getw() const;
  int geth() const;
  int gettilew() const;
  int gettileh() const;
  tile *gettile(int x, int y);
  void tick();
  void draw();
  std::pair<int, int> movemonster(monster *m, int x, int y);

  int blocking;
  void insertmonster(std::unique_ptr<monster> m);
};
