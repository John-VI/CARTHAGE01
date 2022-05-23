// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <stdexcept>
#include <string>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "clkwin.h"

#include "clktex.h"

clk::sprite::sprite(window &renderer, const char filename[],
		    SDL_Rect *viewport) : renderer(renderer), texture(nullptr, &SDL_DestroyTexture), viewport(viewport) {
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface)
    throw std::runtime_error(std::string({ "IMG_Load failed: ", IMG_GetError() }));
  
  SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer.getSDL_Renderer(), surface);
  SDL_FreeSurface(surface);
  if (!tex)
    throw std::runtime_error(std::string({ "SDL_CreateTextureFromSurface failed: ", SDL_GetError() }));
  texture.reset(tex);

  int w, h;
  query(nullptr, nullptr, &w, &h);
  sheetoffset = { 0, 0, w, h };
}

clk::sprite::~sprite() = default;

int clk::sprite::query(uint32_t *format, int *access, int *w, int *h) const {
  int ret = SDL_QueryTexture(texture.get(), format, access, w, h);
  if (ret)
    throw std::runtime_error(std::string({ "SDL_QueryTexture failed: ", SDL_GetError() }));
  return ret;
}

SDL_Rect clk::sprite::draw(int x, int y) {
  SDL_Rect region = { screenoffset.x + x + viewport->x, screenoffset.y + y + viewport->y, screenoffset.w, screenoffset.h };
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &sheetoffset, &region);
  return region;
}

SDL_Rect clk::sprite::drawchar(int x, int y, char c) {
  SDL_Rect srcregion = { sheetoffset.x + c - startchar, sheetoffset.y, sheetoffset.w, sheetoffset.h };
  SDL_Rect dstregion = { screenoffset.x + x + viewport->x, screenoffset.y + y + viewport->y, screenoffset.w, screenoffset.h };
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &srcregion, &dstregion);
  return dstregion;
}

SDL_Rect clk::sprite::drawstring(int x, int y, const std::string& str) {
  for (int i = 0; i < str.length(); i++)
    this->drawchar(x + sheetoffset.w * i, y, str.at(i));

  return { x + screenoffset.x, y + screenoffset.y, screenoffset.w * (int)str.length(), screenoffset.h };
}
