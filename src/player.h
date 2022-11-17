// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkinputtrigger.h"

#include "hitbox.h"
#include "ship.h"

#include <memory>
#include <bitset>

namespace clk {
  class keybind;
}

class player : public controller {
protected:
  struct playertrig : public clk::inputtrigger {
    player &binding;
    playertrig(player &bind);
    void trigger(const SDL_Event &e) override;
  };

  clk::keybind &keybinder;
  std::shared_ptr<playertrig> kbdblock;

  std::bitset<4> movestate = 0;

public:
  player(ship *t, clk::keybind &manager);

  void managerreg();
  void managerdereg();

  void update(const SDL_Event &e);
};
