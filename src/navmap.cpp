// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "navmap.h"

#include "sdarray.h"

#include <functional>

#define CHKSIZE(X)                                                             \
  if (getx() != X.getx() || gety() != X.gety())                                \
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

  return *this;
}

// navmap navmap::operator*(const navmap &other) const {
//   CHKSIZE(other);
//   navmap nmap(getx(), gety());

//   for (int i = 0; i < size(); i++)
//     nmap[i] = (*this)[i] * other[i];

//   return nmap;
// }

navmap navmap::operator*(int x) const {
  navmap nmap(getx(), gety());

  for (int i = 0; i < size(); i++)
    nmap[i] = (*this)[i] * x;

  return nmap;
}

navmap &navmap::operator*=(int x) {
  for (int i = 0; i < size(); i++)
    (*this)[i] *= x;

  return *this;
}

navmap navmap::operator-() const {
  navmap nmap(getx(), gety());

  for (int i = 0; i < size(); i++)
    nmap[i] = -(*this)[i];

  return nmap;
}

navmap navmap::operator-(const navmap &other) const {
  CHKSIZE(other);
  navmap nmap(getx(), gety());

  for (int i = 0; i < size(); i++)
    nmap[i] = (*this)[i] - other[i];

  return nmap;
}

navmap &navmap::operator-=(const navmap &other) {
  CHKSIZE(other);

  navmap nmap(getx(), gety());

  for (int i = 0; i < size(); i++)
    (*this)[i] -= other[i];

  return *this;
}

inline int navmap::chkpos(int x, int y) { return x + (y * this->x); }

navmap navmap::bleed(std::function<int, int> func) const {
  navmap nmap(x, y);

  for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++)
      if ((*this)[chkpos(j, i)] > 0) {
        nmap[chkpos(j, i)] = (*this)[chkpos(j, i)];
        if (j > 0)
          nmap[chkpos(j - 1, i)] = func((*this)[chkpos(j - 1, i)]);
        if (j < this->x)
          nmap[chkpos(j + 1, i)] = func((*this)[chkpos(j + 1, i)]);
        if (i > 0)
          nmap[chkpos(j, i - 1)] = func((*this)[chkpos(j, i - 1)]);
        if (i < this->y)
          nmap[chkpos(j, i + 1)] = func((*this)[chkpos(j, i + 1)]);
      }
  return nmap;
}
