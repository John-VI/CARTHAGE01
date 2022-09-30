// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <array>

#include "tile.h"
#include "tileflag.h"

#include <bitset>
#include <stdexcept>
#include <unordered_map>

// const std::unordered_map<tiletype, char> tile::tiledefaults = {
//     {tiletype::WALL, (char)tileflag::DESTRUCT},
//     {tiletype::MAX, (char)tileflag::PASSABLE | (char)tileflag::TRANSLUC}};

const std::array<tiledef, (int)tiletype::MAX> tile::ttypes = {
    {{tileflag::TRANSLUC | tileflag::PASSABLE, 0, ' '},
     {tileflag::PASSABLE | tileflag::DESTRUCT | tileflag::TRANSLUC, 100, '.'},
     {(tflags)(TILEFLAG_UNDERLYING)tileflag::DESTRUCT, 100, '#'}}};

void tile::mktype(tiletype newtype) { type = newtype; }

tflags tile::flags() {
  return feat.get() ? feat.get()->flags() : ttypes[(int)type].flags;
}
