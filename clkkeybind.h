// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkinputtrigger.h"

#include <unordered_map>

#include "clkinputman.h"

namespace clk {

class keybind {
protected:
  struct kbdbtrig : public inputtrigger {
    keybind &binding;
    kbdbtrig(keybind &bind);
  };
  int registration;
  inputman *manager = nulptr;
  std::unordered_map<SDL_Keycode, inputtrigger> registrations;

public:
  void trigger(const SDL_Event &e);
  void managerreg(inputman *manager);
  void managerdereg();
  int registerinput(SDL_KeyCode code,
                    std::unique_ptr<inputtrigger> newtrigger);
  void deregister(SDL_KeyCode code, int id);
};

} // namespace clk