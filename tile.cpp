// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <array>

#include "tile.h"

#include <stdexcept>
#include <unordered_map>
#include <bitset>

// const std::unordered_map<tiletype, char> tile::tiledefaults = {
//     {tiletype::WALL, (char)tileflag::DESTRUCT},
//     {tiletype::MAX, (char)tileflag::PASSABLE | (char)tileflag::TRANSLUC}};

const std::array<tiledef, (int)tiletype::MAX> tile::ttypes = {
  {tileflag::TRANSLUC | tileflag::PASSABLE, 0, ' '},
  {tileflag::PASSABLE | tileflag::}
}

void tile::mktype(tiletype newtype) {
  type = newtype;

  try {
    flags = tiledefaults.at(type);
  } catch (std::out_of_range) {
    flags = tiledefaults.at(tiletype::MAX);
  }
}
