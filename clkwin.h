// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
#pragma once

typedef SDL_Color struct SDL_Color;
typedef SDL_Window struct SDL_Window;
typedef SDL_Renderer struct SDL_Renderer;

namespace clk {
  class window {
    SDL_Color& color;
    SDL_Window *window;
    SDL_Renderer *renderer;

  public:
    window(const char name[], int width, int height, SDL_Color& color);
    ~window();
    void setcolor(const SDL_Color& newcolor);
    SDL_Window *getSDL_Window();
    SDL_Renderer *getSDL_Renderer();
  };
}
