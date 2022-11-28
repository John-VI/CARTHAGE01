// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "hitbox.h"

#include <SDL2/SDL_rect.h>

hitbox::hitbox() = default;
hitbox::hitbox(const SDL_Rect &rect) : SDL_Rect(rect) {}
