// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <memory>
#include <unordered_map>

typedef struct monster monster;
typedef struct feature feature;

enum class tiletype : char { UNDEF, FLOOR, WALL, MAX };
enum class tilefeature : char { NONE, USTAIR, DSTAIR, GOLD, MAX };

enum class tileflag : char {
  PASSABLE = 0b00000001,
  DESTRUCT = 0b00000010,
  TRANSLUC = 0b00000100
};

struct tiledef {
  short health;
  char tile;
  char flags;
};

struct tile {
  tiletype type = tiletype::UNDEF;
  std::unique_ptr<feature> feature = nullptr;
  char placeholder;
  short health = 1000;
  monster *mon = nullptr;

  static const std::array<tiledef, (int)tiletype::MAX> ttypes;

  void mktype(tiletype newtype);
  template <class T> void mkfeat();
  void setfeat(tilefeature *newfeature);

  char flags();
};

template <class T> void tile::mkfeat() { feature = new T(*this); }
