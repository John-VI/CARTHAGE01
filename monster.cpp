// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "monster.h"

#include <string>

#include "clktex.h"

#include "grid.h"
#include "tile.h"

monster::monster(const int type, const char family,
		 std::string name) : type(type), family(family),
				     name(name) { }

monster::~monster() { g->gettile(x, y)->mon = nullptr; }

int monster::tick() {
  meter -= speed;
  if (meter <= 0) {
    ai();
    meter += 100;
  }
  return meter;
}

void monster::draw() {
  g->font.drawchar(x * g->gettilew(), y * g->gettileh(), family);
}

int monster::hurt(int delta) {
  return hp -= delta;
}

int monster::getx() const {
  return x;
}

int monster::gety() const {
  return y;
}

std::pair<int, int> monster::getcoords() {
  return { x, y };
}

int monster::getmaxhp() const {
  return maxhp;
}

void monster::setmaxhp(int newmax) {
  maxhp = newmax;
}

int monster::gethp() const {
  return hp;
}

int monster::getdamage() const {
  return damage;
}

void monster::setdamage(int newdamage) {
  damage = newdamage;
}

void monster::sethp(int newhp) {
  hp = newhp;
}
