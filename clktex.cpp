// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "clkwin.h"

namespace clk {
  class sprite {
  protected:
    SDL_Rect screenoffset = { 0, 0, 0, 0 };
    SDL_Rect sheetoffset;
    SDL_Texture *texture;
    window& renderer;
    
  public:
    sprite(window &renderer, const char filename[]);
    ~sprite();
    SDL_Rect draw(int x, int y);
    void setscreenoffset(SDL_Rect newoffset);
    void setsheetoffset(SDL_Rect newoffset);
    int getw();
    int geth();
    int query(uint32_t *format, int *access, int *w, int *h);
  };
}

clk::sprite::sprite(window &renderer, const char filename[]) {
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface)
    throw runtime_error(std::string({ "IMG_Load failed: ", IMG_GetError() }));
  
  this->renderer = renderer;
  
  texture = SDL_CreateTextureFromSurface(this->renderer.getSDL_Renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture)
    throw runtime_error(std::string({ "SDL_CreateTextureFromSurface failed: ", SDL_GetError() }));

  sheetoffset = { 0, 0, getw(), geth() };
}

clk::sprite::~sprite() {
  SDL_DestroyTexture(texture);
}

int clk::sprite::query(uint32_t *format, int *access, int *w, int *h) {
  int ret = SDL_QueryTexture(texture, format, access, w, h);
  if (ret)
    throw runtime_error(std::string({ "SDL_QueryTexture failed: ", SDL_GetError() }));
  return ret;
}

int clk::sprite::getw() {
  
}
