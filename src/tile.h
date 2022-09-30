// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "tile.h"

#include "feature.h"
#include "tileflag.h"

#include <bitset>
#include <memory>
#include <unordered_map>

typedef struct monster monster;

enum class tiletype : char { UNDEF, FLOOR, WALL, MAX };
enum class tilefeature : char { NONE, USTAIR, DSTAIR, GOLD, MAX };

struct tiledef {
  tflags flags;
  short health;
  char tile;
};

struct tile {
  tiletype type = tiletype::UNDEF;
  std::unique_ptr<feature> feat = nullptr;
  char placeholder;
  short health = 1000;
  monster *mon = nullptr;

  static const std::array<tiledef, (int)tiletype::MAX> ttypes;

  void mktype(tiletype newtype);
  template <class T> void mkfeat();
  void setfeat(tilefeature *newfeature);

  tflags flags();
};

template <class T> void tile::mkfeat() { feat = std::make_unique<T>(*this); }
