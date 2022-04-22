// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause
#pragma once

typedef struct SDL_Color SDL_Color;
typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;

namespace clk {
  class window {
    const SDL_Color *color;
    SDL_Window *win;
    SDL_Renderer *ren;

  public:
    window(const char name[], int width, int height, const SDL_Color *color);
    ~window();
    void setcolor(const SDL_Color *newcolor);
    SDL_Window *getSDL_Window();
    SDL_Renderer *getSDL_Renderer();
  };
}
