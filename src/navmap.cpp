// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "navmap.h"

#include "sdarray.h"

#include <functional>

#define CHKSIZE(X)                            \
  if (getx() != X.getx() || gety() != X.gety())    \
    throw std::runtime_error("Missized matrices.");


navmap::navmap(int x, int y) : sdarray<int>(x * y), x(x), y(y) {}

int navmap::getx() const { return x; }
int navmap::gety() const { return y; }

navmap navmap::operator+(const navmap &other) const {
  CHKSIZE(other);

  navmap nmap(getx(), gety());

  for (int i = 0; i < size(); i++)
    nmap[i] = (*this)[i] + other[i];

  return nmap;
}

navmap &navmap::operator+=(const navmap &other) {
  CHKSIZE(other);

  for (int i = 0; i < size(); i++)
    (*this)[i] += other[i];
}
