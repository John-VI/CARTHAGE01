// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "navmap.h"

#include "sdarray.h"

#include <functional>

#define CHKSIZE(X)                                                             \
  if (getx() != X.getx() || gety() != X.gety())                                \
    throw std::runtime_error("Missized matrices.");

navmap::navmap(int x, int y) : sdarray(x * y), x(x), y(y) {
  for (int i = 0; i < size(); i++)
    (*this)[i] = 0;
}

navmap::navmap(navmap &&) = default;

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

inline int navmap::chkpos(int x, int y) const { return x + (y * this->x); }

navmap navmap::bleed(std::function<int(int)> func) const {
  navmap nmap(x, y);

  for (int i = 0; i < y; i++)
    for (int j = 0; j < x; j++)
      if ((*this)[chkpos(j, i)] > 0) {
        nmap.at(chkpos(j, i)) = at(chkpos(j, i));
        int mod = func(at(chkpos(j, i)));
        if (j > 0 && mod > nmap.at(chkpos(j - 1, i)))
          nmap.at(chkpos(j - 1, i)) = mod;
        if (j < this->x - 1 && mod > nmap.at(chkpos(j + 1, i)))
          nmap.at(chkpos(j + 1, i)) = mod;
        if (i > 0 && mod > nmap.at(chkpos(j, i - 1)))
          nmap.at(chkpos(j, i - 1)) = mod;
        if (i < this->y - 1 && mod > nmap.at(chkpos(j, i + 1)))
          nmap.at(chkpos(j, i + 1)) = mod;
      }

  return nmap;
}

bool navmap::operator==(const navmap &other) {
  if (getx() != other.getx() || gety() != other.gety())
    return false;
  for (int i = 0; i < size(); i++)
    if ((*this)[i] != other[i])
      return false;
  return true;
}

navmap navmap::bleedout() {
  navmap newmap(getx(), gety());
  navmap oldmap(getx(), gety());
  oldmap = *this;

  while ((newmap = oldmap.bleed([](int x) { return x / 3; })) != oldmap) {
    oldmap = newmap;
  }

  // for (int i = 0; i < 5; i++)
  //   oldmap = oldmap.bleed([](int x) { return x / 3; });
  // newmap = oldmap;

  return newmap;
}

navmap &navmap::operator=(const navmap &other) {
  CHKSIZE(other);

  for (int i = 0; i < size(); i++)
    (*this)[i] = other[i];
  return *this;
}

navmap::navmap(const navmap &other)
    : sdarray<int>(other.getx() * other.gety()), x(other.getx()),
      y(other.gety()) {
  for (int i = 0; i < size(); i++)
    (*this)[i] = other[i];
}
