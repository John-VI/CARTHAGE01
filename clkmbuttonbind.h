// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkinputtrigger.h"

#include <unordered_map>

#include "clkinputman.h"

namespace clk {

class mbuttonbind {
protected:
  struct mbuttontrig : public inputtrigger {
    mbuttonbind &binding;
    mbuttontrig(mbuttonbind &bind);
    void trigger(const SDL_Event &e) override;
    ~mbuttontrig();
  };
  int registration;
  inputman *manager = nullptr;
  std::unordered_map<char, std::unique_ptr<inputtrigger>> registrations;

public:
  mbuttonbind();

  void trigger(const SDL_Event &e);
  void managerreg(inputman *manager);
  void managerdereg();
  void registerinput(char, inputtrigger *newtrigger);
  void deregister(char);
};

} // namespace clk
