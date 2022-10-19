// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkinputtrigger.h"

#include <string>
#include <unordered_map>
// #include <vector>

#include "clkinputman.h"
#include "clkkeybind.h"
#include "clktex.h"

namespace clk {

class menubuild {
protected:
  struct menubuildktrig : public inputtrigger {
    menubuild &binding;
    menubuildktrig(menubuild &binding, double *val);
    void trigger(const SDL_Event &e) override;
    ~menubuildktrig();
    double *val;
  };
  struct menubuildmtrig : public inputtrigger {
    menubuild &binding;
    menubuildmtrig(menubuild &binding);
    void trigger(const SDL_Event &e) override;
    ~menubuildmtrig();
  };
  // std::vector<int> registrations;
  inputman &mmanager;
  int registration;
  keybind &kmanager;
  bool kbound = false;
  sprite &font;
  std::string buffer;

  double *target = nullptr;

public:
  menubuild(std::unordered_map<SDL_Keycode, double *> mappings, inputman &,
            keybind &, sprite &font);
  ~menubuild();
  std::unordered_map<SDL_Keycode, double *> mappings;

  void ktrigger(const SDL_Event &e, double *val);
  void kmanagerreg();
  void kmanagerdereg();
  void mtrigger(const SDL_Event &e);
  void mmanagerreg();
  void mmanagerdereg();
  void draw();
};

} // namespace clk
