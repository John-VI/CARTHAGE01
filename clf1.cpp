// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clf1.h"

#include "grid.h"
#include "tile.h"

#include <sstream>
#include <utility>

std::pair<unsigned short, unsigned short> prochead(std::istream &level) {
  std::pair<unsigned short, unsigned short> output;
  level.read((char *)&output.first, 2);
  level.read((char *)&output.second, 2);
  ;

  return output;
}

void proctile(tile *t, std::istream &level) {
  level.read((char *)&t->type, 1);
  level.read((char *)&t->feature, 1);
  level.read((char *)&t->flags, 1);
  level.read((char *)&t->placeholder, 1);
  level.read((char *)&t->health, 2);
  level.ignore(2, EOF);
}

grid clf1::decode(std::istream &level, int fonwid, int fonhei,
                  clk::sprite &font) {
  std::pair<unsigned short, unsigned short> dimensions = prochead(level);
  grid output(dimensions, fonwid, fonhei, font);
  tile t[dimensions.first * dimensions.second];

  for (unsigned short i = 0; i < dimensions.first * dimensions.second; i++)
    proctile(&t[i], level);

  output.setgrid(t);

  return output;
}
