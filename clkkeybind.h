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
    void trigger(const SDL_Event &e) override;
    ~kbdbtrig();
  };
  int registration;
  inputman *manager = nullptr;
  std::unordered_map<SDL_Keycode, std::unique_ptr<inputtrigger>> registrations;

public:
  keybind();
  //  keybind(
  //      std::unordered_map<SDL_Keycode, std::unique_ptr<inputtrigger>>
  //      basemap);
  void trigger(const SDL_Event &e);
  void managerreg(inputman *manager);
  void managerdereg();
  void registerinput(SDL_KeyCode code, inputtrigger *newtrigger);
  void deregister(SDL_KeyCode code);
};

} // namespace clk