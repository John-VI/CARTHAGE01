// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "feature.h"

#include "tile.h"

class door : public feature {
  bool open;

  static const char closedflags = (char)tileflag::DESTRUCT;
  static const char openflags =
      (char)tileflag::PASSABLE | (char)tileflag::TRANSLUC;

  void toggle();

public:
  door(tile &);

  void act(monster &) override;
};
