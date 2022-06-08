// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <stdexcept>
#include <string>
#include <memory>

#include <SDL2/SDL.h>

#include "clkwin.h"

using namespace clk;

clk::window::window(const char name[], int width, int height, const SDL_Color *color) : color(color), win(nullptr, &SDL_DestroyWindow), ren(nullptr, &SDL_DestroyRenderer) {
  SDL_Window *window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED,
			 SDL_WINDOWPOS_UNDEFINED, width, height,
			 SDL_WINDOW_SHOWN);
  if (window == nullptr)
    throw std::runtime_error(std::string({ "Failed to initialize SDL window: ", SDL_GetError() }));
  win.reset(window);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr)
    throw std::runtime_error(std::string({ "Failed to initialize SDL renderer: ", SDL_GetError() }));
  ren.reset(renderer);
  setcolor(color);
}

clk::window::~window() = default;

void clk::window::setcolor(const SDL_Color *newcolor) {
  color = newcolor;
  SDL_SetRenderDrawColor(ren.get(), color->r, color->g, color->b, color->a);
}

SDL_Window *clk::window::getSDL_Window() {
  return win.get();
}

SDL_Renderer *clk::window::getSDL_Renderer() {
  return ren.get(); }

void clk::window::clear() { SDL_RenderClear(ren.get()); }
void clk::window::draw() { SDL_RenderPresent(ren.get()); }