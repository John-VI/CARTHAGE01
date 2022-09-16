// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <SDL2/SDL_render.h>
#include <memory>
#include <stdexcept>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "clkwin.h"

#include "clktex.h"

clk::sprite::sprite(window &ren, const char filename[])
    : texture(nullptr, &SDL_DestroyTexture), renderer(ren) {
  SDL_Surface *surface = IMG_Load(filename);
  if (!surface)
    throw std::runtime_error(std::string(IMG_GetError()));

  SDL_Texture *tex =
      SDL_CreateTextureFromSurface(renderer.getSDL_Renderer(), surface);
  SDL_FreeSurface(surface);
  if (!tex)
    throw std::runtime_error(std::string(SDL_GetError()));
  texture.reset(tex);

  int w, h;
  query(nullptr, nullptr, &w, &h);
  sheetoffset = {0, 0, w, h};
  screenoffset = sheetoffset;
}

clk::sprite::~sprite() = default;

int clk::sprite::query(uint32_t *format, int *access, int *w, int *h) const {
  int ret = SDL_QueryTexture(texture.get(), format, access, w, h);
  if (ret)
    throw std::runtime_error(std::string(SDL_GetError()));
  return ret;
}

SDL_Rect clk::sprite::draw(vports port, int x, int y) {
  const viewport &viewport = renderer.getviewport(port);
  SDL_Rect region = {screenoffset.x + x + viewport.x,
                     screenoffset.y + y + viewport.y, screenoffset.w,
                     screenoffset.h};
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &sheetoffset,
                 &region);
  return region;
}

SDL_Rect clk::sprite::draw(viewport &viewport, int x, int y) {
  SDL_Rect region = {screenoffset.x + x + viewport.x,
                     screenoffset.y + y + viewport.y, screenoffset.w,
                     screenoffset.h};
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &sheetoffset,
                 &region);
  return region;
}

void clk::sprite::setscreenoffset(SDL_Rect newoffset) {
  screenoffset = newoffset;
}

void clk::sprite::setsheetoffset(SDL_Rect newoffset) {
  sheetoffset = newoffset;
}

SDL_Rect clk::sprite::drawchar(vports port, int x, int y, char c) {
  const viewport &viewport = renderer.getviewport(port);
  SDL_Rect srcregion = {sheetoffset.x + (c - startchar) * sheetoffset.w,
                        sheetoffset.y, sheetoffset.w, sheetoffset.h};
  SDL_Rect dstregion = {screenoffset.x + x + viewport.x,
                        screenoffset.y + y + viewport.y, screenoffset.w,
                        screenoffset.h};
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &srcregion,
                 &dstregion);
  return dstregion;
}

SDL_Rect clk::sprite::drawchar(viewport &viewport, int x, int y, char c) {
  SDL_Rect srcregion = {sheetoffset.x + (c - startchar) * sheetoffset.w,
                        sheetoffset.y, sheetoffset.w, sheetoffset.h};
  SDL_Rect dstregion = {screenoffset.x + x + viewport.x,
                        screenoffset.y + y + viewport.y, screenoffset.w,
                        screenoffset.h};
  SDL_RenderCopy(renderer.getSDL_Renderer(), texture.get(), &srcregion,
                 &dstregion);
  return dstregion;
}

SDL_Rect clk::sprite::drawstring(vports port, int x, int y,
                                 const std::string &str) {
  for (int i = 0; i < str.length(); i++)
    drawchar(port, x + sheetoffset.w * i, y, str.at(i));

  return {x + screenoffset.x, y + screenoffset.y,
          screenoffset.w * (int)str.length(), screenoffset.h};
}

SDL_Rect clk::sprite::drawstring(viewport &viewport, int x, int y,
                                 const std::string &str) {
  for (int i = 0; i < str.length(); i++)
    drawchar(viewport, x + sheetoffset.w * i, y, str.at(i));

  return {x + screenoffset.x, y + screenoffset.y,
          screenoffset.w * (int)str.length(), screenoffset.h};
}

int clk::sprite::getw() const {
  int w;
  SDL_QueryTexture(texture.get(), nullptr, nullptr, &w, nullptr);
  return w;
}

int clk::sprite::geth() const {
    int h;
SDL_QueryTexture(texture.get(), nullptr, nullptr, nullptr, &h);
return h;
}
