// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "grid.h"

#include <cassert>
#include <forward_list>
#include <memory>
#include <stdexcept>

#include "clktex.h"

#include "messaging.h"
#include "monster.h"
#include "tile.h"

grid::grid(int width, int height, int tilewidth, int tileheight,
           clk::sprite &font)
    : w(width), h(height), twidth(tilewidth), theight(tileheight), font(font) {
  std::list<std::unique_ptr<monster>> monsters;
  tiles = std::make_unique<tile[]>(w * h);
  blocking = 0;

  for (int i = 0; i < width * height; i++) {
    tile *t = tiles.get() + i;
    t->mktype((i % 7) ? tiletype::FLOOR : tiletype::WALL);
  }
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
  if (!blocking)
    for (auto &moving : monsters) {
      moving.get()->tick();
      if (blocking)
        break;
    }
}

void grid::draw() {
  tile *t;
  for (int i = 0; i < w * h; i++) {
    t = tiles.get() + i;
    assert(tiles.get() + i == &(tiles.get()[i]));
    if (t->mon == nullptr)
      font.drawchar(vports::GRID, (i % w) * twidth, (i / h) * theight,
                    (t->flags & (char)tileflag::PASSABLE) ? '.' : '#');
    else
      t->mon->draw();
  }
}

std::pair<int, int> grid::movemonster(monster *m, int x, int y) {
  messages::push(
      {"Monster move request", severitylevel::NORMAL, devlevel::GAME, 0});
  tile *dest = gettile(x, y);
  if (!dest->mon && dest->flags & (char)tileflag::PASSABLE) {
    gettile(m->getx(), m->gety())->mon = nullptr;
    dest->mon = m;
    m->setx(x);
    m->sety(y);
    return std::pair<int, int>(x, y);
  } else
    return m->getcoords();
}

void grid::insertmonster(std::unique_ptr<monster> m) {
  monsters.push_front(std::move(m));
  tiles[0].mon = monsters.front().get();
}
