// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <SDL2/SDL_events.h>

class inputtrigger {
 public:
  int id;
  virtual void trigger(const SDL_Event &e) = 0;
};
