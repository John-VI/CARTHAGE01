// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

typedef struct tile tile;
typedef struct monster monster;

class feature {
public:
  feature(tile &);

  char sprite = '\0';

  char fflags = 0;

  virtual void step(monster &);
  virtual void hit(monster &);
  virtual void act(monster &);
  virtual void tick();

  char flags();

private:
  tile &t;
};
