// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clf1.h"
#include "clkinputtrigger.h"

#include <deque>
#include <memory>
#include <string>

namespace clk {
typedef struct sprite sprite;
typedef struct keybind keybind;
} // namespace clk

typedef struct grid grid;

class gridman {
private:
  struct lltrig : public clk::inputtrigger {
    gridman &binding;
    lltrig(gridman &);
    void trigger(const SDL_Event &e) override;
    ~lltrig();
  };
  clf1::levelloader lloader;
  std::deque<std::shared_ptr<grid>> levels;
  clk::sprite &font;
  clk::keybind &kman;

  bool bound = false;

  SDL_Keycode ltrig = SDLK_o;
  SDL_Keycode strig = SDLK_p;

public:
  std::shared_ptr<grid> clevel;
  std::string filename = "default.clf1";

  gridman(clk::sprite &font, clk::keybind &kbdmanager);

  void managerreg();
  void managerdereg();
  void load();
  void save();
  void trigger(const SDL_Event &e);
};
