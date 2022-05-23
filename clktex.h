// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <memory>

#include <SDL2/SDL.h>

typedef struct window window;

namespace clk {
  const unsigned int startchar = 32;

  class sprite {
  protected:
    SDL_Rect screenoffset = { 0, 0, 0, 0 };
    SDL_Rect sheetoffset;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
    window& renderer;

    SDL_Rect *viewport = nullptr;

  public:
    sprite(window& renderer, const char filename[],
	   SDL_Rect *viewport);
    ~sprite();
    SDL_Rect draw(int x, int y) ;
    void setscreenoffset(SDL_Rect newoffset);
    void setsheetoffset(SDL_Rect newoffset);
    int getw() const;
    int geth() const;
    int query(uint32_t* format, int *access, int *w, int *h) const;
    SDL_Rect drawchar(int x, int y, char c);
    SDL_Rect drawstring(int x, int y, const std::string& str);
    SDL_Rect griddrawchar(int r, int d, char c) const;
    SDL_Rect griddrawstring(int r, int d, std::string& str);
  };
}
