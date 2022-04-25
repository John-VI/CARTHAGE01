// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <stdexcept>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "clkwin.h"

namespace clk {
  class sprite {
  protected:
    SDL_Rect screenoffset = { 0, 0, 0, 0 };
    SDL_Rect sheetoffset;
    std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;
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

clk::sprite::sprite(window &renderer, const char filename[]) : renderer(renderer), texture(nullptr, &SDL_DestroyTexture) {
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface)
    throw std::runtime_error(std::string({ "IMG_Load failed: ", IMG_GetError() }));
  
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer.getSDL_Renderer(), surface);
  SDL_FreeSurface(surface);
  if (!tex)
    throw std::runtime_error(std::string({ "SDL_CreateTextureFromSurface failed: ", SDL_GetError() }));
  texture.reset(tex);

  int w, h;
  query(NULL, NULL, &w, &h);
  sheetoffset = { 0, 0, w, h };
}

clk::sprite::~sprite() = default;

int clk::sprite::query(uint32_t *format, int *access, int *w, int *h) {
  int ret = SDL_QueryTexture(texture.get(), format, access, w, h);
  if (ret)
    throw std::runtime_error(std::string({ "SDL_QueryTexture failed: ", SDL_GetError() }));
  return ret;
}

