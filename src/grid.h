// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <list>
#include <memory>
#include <utility>

#include "monster.h"
#include "protomonster.h"
#include "tile.h"

namespace clk {
typedef struct sprite sprite;
typedef struct keybind keybind;
} // namespace clk

class grid {
  unsigned short w;
  unsigned short h;
  int twidth;
  int theight;
  // std::list<std::unique_ptr<monster>> monsters;
  std::unique_ptr<tile[]> tiles;
  clk::keybind *kman = nullptr;

public:
  std::list<std::unique_ptr<monster>> monsters;

  grid(unsigned short width, unsigned short height, int tilewidth,
       int tileheight, clk::sprite &font);
  grid(std::pair<unsigned short, unsigned short>, int tilewidth, int tileheight,
       clk::sprite &font);

  void setgrid(tile tiles[]);
  clk::sprite &font;

  unsigned short getw() const;
  unsigned short geth() const;
  int gettilew() const;
  int gettileh() const;
  tile *gettile(unsigned short x, unsigned short y);
  tile *gettile(unsigned long x); // nick fuentes catboys
  const tile *gettile(unsigned long x) const;
  const tile *gettile(unsigned short x, unsigned short y) const;
  void tick();
  void draw();
  std::pair<unsigned short, unsigned short>
  movemonster(monster *m, unsigned short x, unsigned short y);

  int blocking;
  void insertmonster(std::unique_ptr<monster> m);
  void insertmonster(monster *m);
  std::pair<unsigned short, unsigned short>
  newmonst(protomonster::montype type);

  void managerreg(clk::keybind *kbdman);
  void managerdereg();

  /*
  ~grid();
  grid(const grid &other);
  grid &operator=(const grid &other);

  grid(const grid &&other);
  grid &operator=(grid &&other);
  */
};
