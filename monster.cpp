// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "monster.h"

#include <string>

#include "clktex.h"

#include "grid.h"

monster::monster(const int type, const char family,
		 std::string name) : type(type), family(family),
				     name(name) { }

int monster::tick() {
  meter -= speed;
  if (meter <= 0) {
    ai();
    meter += 100;
  }
  return meter;
}

void monster::draw() {
  g->font.drawchar(x * g->pw, y * g->ph, family);
}

int monster::hurt(int delta) {
  return hp -= delta;
}

int monster::getx() {
  return x;
}

int monster::gety() {
  return y;
}

std::pair<int, int> monster::getcoords() {
  return { x, y };
}

int monster::getmaxhp() {
  return maxhp;
}

void monster::setmaxhp(int newmax) {
  maxhp = newmax;
}

int monster::gethp() {
  return hp;
}

int monster::getdamage() {
  return damage;
}

void monster::setdamage(int newdamage) {
  damage = newdamage;
}

void monster::sethp(int newhp) {
  hp = newhp;
}
