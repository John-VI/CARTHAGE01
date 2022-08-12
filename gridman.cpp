// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "gridman.h"

#include "clf1.h"
#include "clkinputtrigger.h"
#include "clkkeybind.h"
#include "clktex.h"
#include "grid.h"

#include <deque>
#include <exception>
#include <memory>
#include <string>

gridman::lltrig::lltrig(gridman &g) : binding(g) {}
void gridman::lltrig::trigger(const SDL_Event &e) { binding.trigger(e); }
gridman::lltrig::~lltrig() = default;

gridman::gridman(clk::sprite &f, clk::keybind &k)
    : font(f), kman(k), lloader(f) {}

void gridman::managerreg() {
  if (bound)
    return;
  kman.registerinput(ltrig, new lltrig(*this));
  kman.registerinput(strig, new lltrig(*this));

  clevel.get()->managerreg(&kman);

  bound = true;
}

void gridman::managerdereg() {
  if (!bound)
    return;
  kman.deregister(ltrig);
  kman.deregister(strig);

  clevel.get()->managerdereg();

  bound = false;
}

void gridman::load() {
  std::shared_ptr<grid> newlvl(lloader.load(filename));
  if (!levels.empty())
    levels.pop_back();

  levels.push_front(newlvl);
  clevel = newlvl;

  if (bound)
    clevel.get()->managerreg(&kman);
}

void gridman::save() { lloader.save(*clevel.get(), filename); }

void gridman::trigger(const SDL_Event &e) {
  if (e.key.keysym.sym == ltrig)
    load();
  else if (e.key.keysym.sym == strig)
    save();
}
