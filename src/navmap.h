// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "sdarray.h"

#include <functional>

class navmap : public sdarray<int> {
 private:
  int x, y;

 public:
  navmap(int x, int y);

  int getx() const;
  int gety() const;

  int bleed(std::function<int>);

  navmap operator+(const navmap &other) const;
  navmap &operator+=(const navmap &other);

  navmap operator-(const navmap &other) const;
  navmap &operator-=(const navmap &other);

  navmap operator*(int) const;
  navmap &operator*=(int);

  navmap operator-() const;

  navmap &operator=(const navmap &other);
};
