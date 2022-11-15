// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkinputtrigger.h"

#include "clkinputman.h"

namespace clk {

class terminator {
protected:
  struct quittrig : public inputtrigger {
    terminator &binding;
    quittrig(terminator &bind);
    void trigger(const SDL_Event &e) override;
    ~quittrig();
  };
  int registration;
  inputman *manager = nullptr;
  int &quitsignal;
  std::shared_ptr<quittrig> registblock;

public:
  terminator(int &signaler);
  void terminate();
  void managerreg(inputman *manager);
  void managerdereg();
};

} // namespace clk
