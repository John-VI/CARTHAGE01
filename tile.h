// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "tile.h"

#include "tileflag.h"

#include <memory>
#include <unordered_map>
#include <bitset>

typedef struct monster monster;
typedef struct feature feature;

enum class tiletype : char { UNDEF, FLOOR, WALL, MAX };
enum class tilefeature : char { NONE, USTAIR, DSTAIR, GOLD, MAX };

struct tiledef {
  std::bitset<TILEFLAG_SIZE> flags;
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

  std::bitset<TILEFLAG_SIZE> flags();
};

template <class T> void tile::mkfeat() { feat = new T(*this); }
