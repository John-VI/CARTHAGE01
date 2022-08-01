// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <unordered_map>

typedef struct monster monster;

enum class tiletype : char { UNDEF, FLOOR, WALL, MAX };
enum class tilefeature : char { NONE, USTAIR, DSTAIR, GOLD };

enum class tileflag : char {
  PASSABLE = 0b00000001,
  DESTRUCT = 0b00000010,
  TRANSLUC = 0b00000100
};

struct tile {
  tiletype type = tiletype::UNDEF;
  tilefeature feature = tilefeature::NONE;
  char flags;
  char placeholder;
  short health = 1000;
  monster *mon = nullptr;

  static const std::unordered_map<tiletype, char> tiledefaults;
  void mktype(tiletype newtype);
  void mkfeat(tilefeature newfeature);
};
