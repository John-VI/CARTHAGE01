// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "grid.h"

#include <forward_list>
#include <memory>
#include <stdexcept>
#include <cassert>

#include "clktex.h"

#include "monster.h"
#include "tile.h"

grid::grid(int width, int height, int tilewidth, int tileheight,
           clk::sprite &font)
    : w(width), h(height), twidth(tilewidth), theight(tileheight), font(font) {
  tiles = std::unique_ptr<tile[]>(new tile[w * h]);
}

int grid::getw() const { return w; }
int grid::geth() const { return h; }
int grid::gettilew() const { return twidth; }
int grid::gettileh() const { return theight; }

tile *grid::gettile(int x, int y) {
  if (x >= w || x < 0 || y >= h || y < 0)
    throw std::runtime_error("Tile grid reference out of bounds.");
  return tiles.get() + x + y * w;
}

void grid::tick() {
  for (auto &moving : monsters) {
    moving.get()->tick();
  }
}

void grid::draw() {
  tile *t;
  for (int i = 0; i < w * h; i++) {
    t = tiles.get() + i;
    assert(tiles.get() + i == &(tiles.get()[i]));
    if (t->mon == nullptr)
      font.drawchar((i % w) * twidth, (i / h) * theight, '.');
  }
}