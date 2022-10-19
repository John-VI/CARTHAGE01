// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <iostream>
#include <string>

// #include "clkinputtrigger.h"

namespace clk {
typedef struct sprite sprite;
// typedef struct keybind keybind;
} // namespace clk
typedef struct grid grid;

namespace clf1 {

class levelloader {
protected:
  /*   SDL_Keycode sbind, lbind;
  clk::keybind &manager;
  bool bound = false; */
  clk::sprite &font;
  // std::string filename;

public:
  levelloader(clk::sprite &font);

  /* void trigger(const SDL_Event &e);
  void managerreg();
  void managerdereg(); */
  grid *load(std::string filename);
  long save(grid &g, std::string filename);
  // void setfilename(std::string);
  std::string getfilename();
};

} // namespace clf1
