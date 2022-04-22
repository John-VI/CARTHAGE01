// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <SDL2/SDL.h>

#include "clkwin.h"

using namespace clk;

clk::window::window(const char name[], int width, int height, const SDL_Color& color) {
  window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED, width, height,
			    SDL_WINDOW_SHOWN);
  if (window == NULL)
    throw runtime_error("Failed to initialize SDL window.");
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (rend == NULL)
    throw runtime_error("Failed to initialize SDL renderer.");
  setcolor(color);
}

clk::window::~window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void clk::window::setcolor(const SDL_Color& newcolor) {
  color = newcolor;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Window *clk::window::getSDL_Window() {
  return window;
}

SDL_Renderer *clk::window::getSDL_Renderer() {
  return renderer;
}
