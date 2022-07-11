// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <memory>

#include <SDL2/SDL.h>

#include <string>

#include "clkviewport.h"
#include "clkwin.h"

namespace clk {
const unsigned int startchar = 32;

class sprite {
protected:
  SDL_Rect screenoffset;
  SDL_Rect sheetoffset;
  std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
  window &renderer;

public:
  sprite(window &renderer, const char filename[]);
  ~sprite();
  SDL_Rect draw(vports port, int x, int y);
  SDL_Rect draw(viewport &port, int x, int y);
  void setscreenoffset(SDL_Rect newoffset);
  void setsheetoffset(SDL_Rect newoffset);
  int getw() const;
  int geth() const;
  int query(uint32_t *format, int *access, int *w, int *h) const;
  SDL_Rect drawchar(vports port, int x, int y, char c);
  SDL_Rect drawchar(viewport &port, int x, int y, char c);
  SDL_Rect drawstring(vports port, int x, int y, const std::string &str);
  SDL_Rect drawstring(viewport &port, int x, int y, const std::string &str);
  SDL_Rect griddrawchar(vports port, int r, int d, char c) const;
  SDL_Rect griddrawchar(viewport &port, int r, int d, char c) const;
  SDL_Rect griddrawstring(vports port, int r, int d, std::string &str);
  SDL_Rect griddrawstring(viewport &port, int r, int d, std::string &str);
};
} // namespace clk
