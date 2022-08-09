// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <iostream>
#include <string>

#include "clkinputtrigger.h"

namespace clk {
typedef struct sprite sprite;
typedef struct keybind keybind;
} // namespace clk
typedef struct grid grid;

namespace clf1 {

class levelloader {
protected:
  struct lltrig : public clk::inputtrigger {
    levelloader &binding;
    lltrig(levelloader &);
    void trigger(const SDL_Event &e) override;
    ~lltrig();
  };
  SDL_Keycode sbind, lbind;
  std::string filename;
  clk::keybind &manager;
  bool bound = false;
  clk::sprite &font;

public:
  levelloader(SDL_Keycode savekey, SDL_Keycode loadkey,
              clk::keybind &kbdmanager, clk::sprite &font,
              std::string filename = "default.clf1");

  void trigger(const SDL_Event &e);
  void managerreg();
  void managerdereg();
  grid load();
  long save(grid &g);
  void setfilename(std::string);
  std::string getfilename();
};

} // namespace clf1
