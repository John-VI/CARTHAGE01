// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "sdarray.h"

#include <functional>

class navmap : public sdarray<int> {
private:
  int x, y;
  inline int chkpos(int x, int y) const;

protected:
  int bleedfunc(int x);

public:
  navmap(int x, int y);

  int getx() const;
  int gety() const;

  navmap bleed(std::function<int(int)>) const;
  navmap &bleedout();

  navmap operator+(const navmap &other) const;
  navmap &operator+=(const navmap &other);

  navmap operator-(const navmap &other) const;
  navmap &operator-=(const navmap &other);

  navmap operator*(int) const;
  navmap &operator*=(int);

  navmap operator-() const;

  navmap &operator=(const navmap &other);
};
