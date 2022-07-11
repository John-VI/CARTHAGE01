// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkkeybind.h"

#include <stdexcept>

clk::keybind::kbdbtrig::kbdbtrig(keybind &bind) : binding(bind) {}

void clk::keybind::kbdbtrig::trigger(const SDL_Event &e) { binding.trigger(e); }

clk::keybind::kbdbtrig::~kbdbtrig() {}

clk::keybind::keybind() = default;

void clk::keybind::trigger(const SDL_Event &e) {
  inputtrigger *itrigger = nullptr;
  try {
    itrigger = registrations.at(e.key.keysym.sym).get();
  } catch (std::out_of_range) {
  }
  if (itrigger)
    itrigger->trigger(e);
}

void clk::keybind::managerreg(inputman *man) {
  if (manager)
    throw std::runtime_error("Already registered with input dispatcher.");
  manager = man;
  registration =
      manager->registerinput(SDL_KEYDOWN, std::make_unique<kbdbtrig>(*this));
}

void clk::keybind::managerdereg() {
  if (manager) {
    manager->deregister(SDL_KEYDOWN, registration);
    manager = nullptr;
  }
}

void clk::keybind::registerinput(SDL_KeyCode code, inputtrigger *newtrigger) {
  if (registrations[code] == nullptr)
    registrations[code].reset(newtrigger);
  else
    throw std::runtime_error("Key is already bound.");
}

void clk::keybind::deregister(SDL_KeyCode code) {
  registrations[code].reset(nullptr);
}