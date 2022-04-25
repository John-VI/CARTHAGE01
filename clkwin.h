// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
#pragma once

#include <memory>

#include <SDL2/SDL.h>

// typedef struct SDL_Color SDL_Color;
// typedef struct SDL_Window SDL_Window;
// typedef struct SDL_Renderer SDL_Renderer;

// void SDL_DestroyRenderer(SDL_Renderer *);
// void SDL_DestroyWindow(SDL_Window *);

namespace clk {
  class window {
    const SDL_Color *color;
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> win;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> ren;

  public:
    window(const char name[], int width, int height, const SDL_Color *color);
    ~window();
    void setcolor(const SDL_Color *newcolor);
    SDL_Window *getSDL_Window();
    SDL_Renderer *getSDL_Renderer();
  };
}
