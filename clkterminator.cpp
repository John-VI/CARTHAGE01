// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkterminator.h"

#include <stdexcept>

clk::terminator::quittrig::quittrig(clk::terminator &bind) : binding(bind){};
void clk::terminator::quittrig::trigger(const SDL_Event &e) {
  binding.terminate();
}

clk::terminator::quittrig::~quittrig() {}

clk::terminator::terminator(int &signaler) : quitsignal(signaler){};

void clk::terminator::managerreg(inputman *man) {
  if (manager)
    throw std::runtime_error("Already registered with input dispatcher.");
  manager = man;
  registration = manager->registerinput(SDL_QUIT, new quittrig(*this));
}

void clk::terminator::managerdereg() {
  manager->deregister(SDL_QUIT, registration);
  manager = nullptr;
}

void clk::terminator::terminate() { quitsignal = 1; }
