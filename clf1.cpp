// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clf1.h"

#include "grid.h"
#include "tile.h"

#include "messaging.h"

#include <iostream>
#include <string>
#include <utility>

std::pair<unsigned short, unsigned short> prochead(std::istream &level) {
  std::pair<unsigned short, unsigned short> output;
  level.read((char *)&output.first, 2);
  level.read((char *)&output.second, 2);

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
  tile *t = new tile[dimensions.first * dimensions.second];

  for (unsigned short i = 0; i < dimensions.first * dimensions.second; i++)
    proctile(&t[i], level);

  output.setgrid(t);

  return output;
}

long mkhead(std::ostream &level, const grid &g) {
  long count = 0;
  std::pair<unsigned short, unsigned short> dimensions{g.getw(), g.geth()};
  level.write((const char *)&dimensions.first, sizeof(dimensions.first));
  count += sizeof(dimensions.first);
  level.write((const char *)&dimensions.second, sizeof(dimensions.second));
  count += sizeof(g.geth());
  return count;
}

long outptile(std::ostream &level, const tile *t) {
  long count = 0;
  level.write((const char *)&t->type, sizeof(t->type));
  count += sizeof(t->type);
  level.write((const char *)&t->feature, sizeof(t->feature));
  count += sizeof(t->feature);
  level.write((const char *)&t->flags, sizeof(t->flags));
  count += sizeof(t->flags);
  level.write((const char *)&t->placeholder, sizeof(t->placeholder));
  count += sizeof(t->placeholder);
  level.write((const char *)&t->health, sizeof(t->health));
  count += sizeof(t->health);
  for (int i = 0; i < sizeof(short); i++) {
    level.put(char(0)); // Screw you
    count += sizeof(char);
  }
  return count;
}

long clf1::encode(std::ostream &level, const grid &g) {
  long header = mkhead(level, g);
  unsigned long i;
  long tiles = 0;
  for (i = 0; i < g.getw() * g.geth(); i++)
    tiles += outptile(level, g.gettile(i));

  messages::push({"Level written. " + std::to_string(header + tiles) +
                      " bytes written. " + std::to_string(i) +
                      " tiles written.",
                  severitylevel::DEV, devlevel::DEV, 0});
  return header + tiles;
}
