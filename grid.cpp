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

grid::grid(unsigned short width, unsigned short height, int tilewidth,
           int tileheight, clk::sprite &font)
    : w(width), h(height), twidth(tilewidth), theight(tileheight), font(font) {
  std::list<std::unique_ptr<monster>> monsters;
  tiles = std::make_unique<tile[]>(w * h);
  blocking = 0;

  for (int i = 0; i < width * height; i++) {
    tile *t = tiles.get() + i;
    t->mktype((i % 7) ? tiletype::FLOOR : tiletype::WALL);
  }
}

grid::grid(std::pair<unsigned short, unsigned short> dimensions, int tilewidth,
           int tileheight, clk::sprite &font)
    : w(dimensions.first), h(dimensions.second), twidth(tilewidth),
      theight(tileheight), font(font) {}

void grid::setgrid(tile t[]) { tiles = std::unique_ptr<tile[]>(t); }

unsigned short grid::getw() const { return w; }
unsigned short grid::geth() const { return h; }
int grid::gettilew() const { return twidth; }
int grid::gettileh() const { return theight; }

tile *grid::gettile(unsigned short x, unsigned short y) {
  if (x >= w || x < 0 || y >= h || y < 0)
    throw std::runtime_error("Tile grid reference out of bounds.");
  return tiles.get() + x + y * w;
}

tile *grid::gettile(unsigned long i) {
  if (i >= w * h)
    throw std::runtime_error("Tile grid reference out of bounds.");
  return tiles.get() + i;
}

const tile *grid::gettile(unsigned short x, unsigned short y) const {
  if (x >= w || x < 0 || y >= h || y < 0)
    throw std::runtime_error("Tile grid reference out of bounds.");
  return tiles.get() + x + y * w;
}

const tile *grid::gettile(unsigned long i) const {
  if (i >= w * h)
    throw std::runtime_error("Tile grid reference out of bounds.");
  return tiles.get() + i;
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
  for (unsigned short i = 0; i < w * h; i++) {
    t = tiles.get() + i;
    assert(tiles.get() + i == &(tiles.get()[i]));
    if (t->mon == nullptr)
      font.drawchar(vports::GRID, (i % w) * twidth, (i / h) * theight,
                    (t->flags & (char)tileflag::PASSABLE) ? '.' : '#');
    else
      t->mon->draw();
  }
}

std::pair<unsigned short, unsigned short>
grid::movemonster(monster *m, unsigned short x, unsigned short y) {
  messages::push(
      {"Monster move request", severitylevel::NORMAL, devlevel::GAME, 0});
  tile *dest = gettile(x, y);
  if (!dest->mon && dest->flags & (char)tileflag::PASSABLE) {
    gettile(m->getx(), m->gety())->mon = nullptr;
    dest->mon = m;
    m->setx(x);
    m->sety(y);
    return std::pair<unsigned short, unsigned short>(x, y);
  } else
    return m->getcoords();
}

void grid::insertmonster(std::unique_ptr<monster> m) {
  monsters.push_front(std::move(m));
  tiles[0].mon = monsters.front().get();
}

/*
grid::~grid() = default;

grid::grid(const grid &g) : w(g.w), h(g.h), twidth(g.twidth), theight(g.theight), monsters(g.monsters), font(g.font),
	blocking(g.blocking) {
		tiles = std::make_unique<tile[]>(w * h);
		for (long i = 0; i < w * h; i++)
			tiles.get()[i] = g.tiles.get()[i];
	}

grid &grid::operator=(const grid &g) {
	if (&g == this)
		return *this;

	w = g.w;
	h = g.h;
	twidth = g.twidth;
	theight = g.theight;
	*/
