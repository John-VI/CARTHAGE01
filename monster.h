// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <string>

#include "clkinputtrigger.h"
#include "clkinputman.h"
#include "clkkeybind.h"

typedef struct grid grid;

class monster {
public:
  monster(const int type, const char family, std::string name, grid *g);
  /* virtual */ ~monster();

  void ai();

  int tick();
  void draw();
  int hurt(int delta);
  std::pair<int, int> move(int newx, int newy);

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

  const int type;
  const char family;

  void trigger(const SDL_Event &e);
  void managerreg(clk::keybind *manager);
  void managerunreg();

protected:
  struct montrig : public clk::inputtrigger {
    monster &binding;
    montrig(monster &bind);
    void trigger(const SDL_Event &e) override;
  };
  clk::keybind *manager = nullptr;

  std::string name;

  grid *g;

  int x, y;

  int maxhp;
  int hp;
  int damage;
  int speed;
  int meter;
  short status = 0;

  void sethp(int newhp);
};
