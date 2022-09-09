// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clf1.h"

#include "grid.h"
#include "tile.h"

#include "messaging.h"

#include <fstream>
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
  level.read((char *)&t->feat, 1);
  level.read((char *)&t->flags, 1);
  level.read((char *)&t->placeholder, 1);
  level.read((char *)&t->health, 2);
  level.ignore(2, EOF);
}

grid *decode(std::istream &level, int fonwid, int fonhei, clk::sprite &font) {
  if (!level.good())
    throw std::runtime_error("Passed bad stream for reading level!");
  std::pair<unsigned short, unsigned short> dimensions = prochead(level);
  grid *output = new grid(dimensions, fonwid, fonhei, font);
  tile *t = new tile[dimensions.first * dimensions.second];

  for (unsigned short i = 0; i < dimensions.first * dimensions.second; i++)
    if (level.good())
      proctile(&t[i], level);
    else
      throw std::runtime_error("Stream went bad while reading level file!");

  output->setgrid(t);

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
  level.write((const char *)&t->feat, sizeof(t->feature));
  count += sizeof(t->feat);
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

long encode(std::ostream &level, const grid &g) {
  if (!level.good())
    throw std::runtime_error("Passed bad stream for writing level!");
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

/* clf1::levelloader::lltrig::lltrig(levelloader &l) : binding(l) {}
clf1::levelloader::lltrig::~lltrig() {}
void clf1::levelloader::lltrig::trigger(const SDL_Event &e) {
  binding.trigger(e);
} */

clf1::levelloader::levelloader(clk::sprite &font) : font(font) {}

/*
void clf1::levelloader::managerreg() {
if (!bound) {
manager.registerinput(sbind, new lltrig(*this));
manager.registerinput(lbind, new lltrig(*this));
}
}

void clf1::levelloader::managerdereg() {
if (bound) {
manager.deregister(sbind);
manager.deregister(lbind);
}
} */

grid *clf1::levelloader::load(std::string filename) {
  std::ifstream levelfile;
  levelfile.open(filename, std::ios::in | std::ios::binary);
  return decode(
      levelfile, 8, 16,
      font); // Relying on destructor close() here for move semantics ease
}

long clf1::levelloader::save(grid &g, std::string filename) {
  std::ofstream levelfile;
  levelfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
  return encode(levelfile, g);
}

/* void clf1::levelloader::trigger(const SDL_Event &e) {
  if (e.key.keysym.sym == sbind)
    save();
  else
    load();
} */
