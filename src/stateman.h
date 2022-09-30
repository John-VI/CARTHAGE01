// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clf1.h"

#include <deque>
#include <memory>

namespace clk {
typedef struct sprite sprite;
typedef struct inputman inputman;
typedef struct keybind keybind;
}; // namespace clk

typedef struct grid grid;

class stateman {
private:
  clf1::levelloader lloader;
  std::deque<std::shared_ptr<grid>> levels;
  clk::sprite &font;
  clk::inputman &iman;
  clk::keybind &kman;

public:
  std::shared_ptr<grid> clevel;
  int state = 0;
};
