// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <string>

typedef struct grid grid;

class monster {
 public:
  monster(const int type, const char family, std::string name);
  virtual ~monster();

  virtual void ai();

  int tick();
  void draw();
  int hurt(int delta);
  std::pair<int, int> move(int newx, int newy);

  int getx();
  int gety();
  std::pair<int, int> getcoords();

  int getmaxhp();
  void setmaxhp(int newmax);
  int gethp();
  int getdamage();
  void setdamage();

  const int type;
  const char family;
 protected:
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
