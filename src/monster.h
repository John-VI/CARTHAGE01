// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <functional>
#include <string>

#include "clkinputman.h"
#include "clkinputtrigger.h"
#include "clkkeybind.h"

#include "protomonster.h"

typedef struct grid grid;

class monster : public protomonster {
public:
  enum class monmode { NONE, ACTING };

  int meter = 0;
  grid *g = nullptr;
  int x, y;
  int hp;
  monmode mode = monmode::NONE;

  monster(protomonster form, enum aitype ai = aitype::MAX); // What the f
  /* virtual */ ~monster();

  int tick();
  void draw();
  int hurt(int delta);

  std::pair<int, int> move(int x, int y);
  std::pair<int, int> act(int x, int y);

  int getx() const;
  int gety() const;
  void setx(int newx);
  void sety(int newy);
  std::pair<int, int> getcoords();

  int getmaxhp() const;
  void setmaxhp(int newmax);
  int gethp() const;
  int getdamage() const;
  void setdamage(int newdamage);

  void trigger(const SDL_Event &e);
  void managerreg(clk::keybind *manager);
  void managerdereg();
  void managerunreg();

protected:
  struct montrig : public clk::inputtrigger {
    monster &binding;
    montrig(monster &bind);
    void trigger(const SDL_Event &e) override;
  };

  clk::keybind *manager = nullptr;
  // int meter;
  void sethp(int newhp);
};
