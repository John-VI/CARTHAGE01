// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "player.h"

#include "clkinputtrigger.h"
#include "clkkeybind.h"

#include "hitbox.h"
#include "ship.h"

#include <SDL2/SDL_scancode.h>
#include <memory>

player::playertrig::playertrig(player &bind) : binding(bind) {}
void player::playertrig::trigger(const SDL_Event &e) {
  binding.update(e);
}

player::player(ship *t, clk::keybind &manager) : controller(t), keybinder(manager) {
  kbdblock = std::make_shared<playertrig>(*this);
  managerreg();
}

inline bool down(const SDL_Event &e) { return e.type == SDL_KEYDOWN; }

void player::update(const SDL_Event &e) {
  switch (e.key.keysym.scancode) {
  case SDL_SCANCODE_W:
    movestate[0] = down(e);
    break;
  case SDL_SCANCODE_S:
    movestate[1] = down(e);
    break;
  case SDL_SCANCODE_A:
    movestate[2] = down(e);
    break;
  case SDL_SCANCODE_D:
    movestate[3] = down(e);
    break;
  default:
    return;
  }

  if (movestate.none()) {
    target->deltax = 0;
    target->deltay = 0;
    return;
  }

  target->deltay = movestate[1] - movestate[0];
  target->deltax = movestate[3] - movestate[2];
}

void player::managerreg() {
  keybinder.registerinput(SDL_SCANCODE_W, kbdblock);
  keybinder.registerinput(SDL_SCANCODE_S, kbdblock);
  keybinder.registerinput(SDL_SCANCODE_A, kbdblock);
  keybinder.registerinput(SDL_SCANCODE_D, kbdblock);
}
