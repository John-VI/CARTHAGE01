// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "monster.h"

#include <string>
#include <stdexcept>

#include "clktex.h"

#include "grid.h"
#include "tile.h"

monster::monster(const int type, const char family, std::string name, grid *g)
    : type(type), family(family), name(name), x(0), y(0), g(g) {
  meter = 100;
  speed = 10;
}

monster::~monster() { g->gettile(x, y)->mon = nullptr; }

int monster::tick() {
  meter -= speed;
  if (meter <= 0) {
    ai();
  }
  return meter;
}

void monster::draw() {
  g->font.drawchar(x * g->gettilew(), y * g->gettileh(), family);
}

int monster::hurt(int delta) { return hp -= delta; }

int monster::getx() const { return x; }

int monster::gety() const { return y; }

std::pair<int, int> monster::getcoords() { return {x, y}; }

int monster::getmaxhp() const { return maxhp; }

void monster::setmaxhp(int newmax) { maxhp = newmax; }

int monster::gethp() const { return hp; }

int monster::getdamage() const { return damage; }

void monster::setdamage(int newdamage) { damage = newdamage; }

void monster::sethp(int newhp) { hp = newhp; }

void monster::ai() { g->blocking = 1; }

void monster::setx(int newx) { x = newx; }
void monster::sety(int newy) { y = newy; }

std::pair<int, int> monster::move(int newx, int newy) {
  if (g->blocking) {
    g->blocking = 0;
    return g->movemonster(this, newx, newy);
  } else
    return std::pair<int, int>(x, y);
}

monster::montrig::montrig(monster &bind) : binding(bind) {}
void monster::montrig::trigger(const SDL_Event &e) { binding.trigger(e); }

void monster::trigger(const SDL_Event &e) {
  switch (e.key.keysym.sym) {
  case SDLK_KP_7:
    move(x - 1, y - 1);
    break;
  case SDLK_KP_8:
    move(x, y - 1);
    break;
  case SDLK_KP_9:
    move(x + 1, y - 1);
    break;
  case SDLK_KP_4:
    move(x - 1, y);
    break;
  case SDLK_KP_6:
    move(x + 1, y);
    break;
  case SDLK_KP_1:
    move(x - 1, y + 1);
    break;
  case SDLK_KP_2:
    move(x, y + 1);
    break;
  case SDLK_KP_3:
    move(x + 1, y + 1);
    break;
  }
  g->blocking = 0;
  meter += 100;
}

void monster::managerreg(clk::keybind *m) {
  if (manager)
    throw std::runtime_error("Already registered with input dispatcher.");
  else
    manager = m;

  for (int i = SDLK_KP_1; i <= SDLK_KP_9; i++)
    manager->registerinput((SDL_KeyCode)i, new montrig(*this));
}