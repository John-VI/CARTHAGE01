// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <SDL2/SDL_rect.h>

struct hitbox : public SDL_Rect {
  hitbox();
  hitbox(const SDL_Rect &);

  inline bool colliding(const hitbox &other) const {
    return x < other.x + other.w && other.x < x + w && y < other.y + other.h &&
           other.y < y + h;
  }

  inline bool within(const SDL_Point &other) const {
    return other.x > x && other.x < x + w && other.y > y && other.y < y + h;
  }
};
