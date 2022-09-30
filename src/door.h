// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "feature.h"

#include "tileflag.h"

#include "tile.h"

class door : public feature {
  bool open;

  static const std::bitset<TILEFLAG_SIZE> closedflags;
  static const std::bitset<TILEFLAG_SIZE> openflags;

  void toggle();
  tflags flags() override;

public:
  door(tile &);

  void act(monster &) override;
};
