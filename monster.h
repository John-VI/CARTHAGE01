// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

class monster {
 public:
  monster(const int type, const char family, std::string name);
  virtual ~monster();

  virtual int tick();
  virtual int hurt(int delta);



  const int type;
  const char family;
 protected:
  std::string name;

  int x, y;

  int maxhp;
  int hp;
  int damage;
  int speed;
  int meter;
  short status;
};
