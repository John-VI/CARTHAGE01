// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkterminator.h"

#include <stdexcept>

#include "messaging.h"

clk::terminator::quittrig::quittrig(clk::terminator &bind) : binding(bind){};
void clk::terminator::quittrig::trigger(const SDL_Event &e) {
  binding.terminate();
}

clk::terminator::quittrig::~quittrig() {}

clk::terminator::terminator(int &signaler) : quitsignal(signaler){};

void clk::terminator::managerreg(inputman *man) {
  if (manager) {
    messages::push({"Already registered with manager.", severitylevel::DEV,
                    devlevel::DEV, 0});
    return;
  }
  manager = man;
  registration = manager->registerinput(SDL_QUIT, new quittrig(*this));
}

void clk::terminator::managerdereg() {
  manager->deregister(SDL_QUIT, registration);
  manager = nullptr;
}

void clk::terminator::terminate() { quitsignal = 1; }
