// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "monster.h"

#include <SDL2/SDL_keycode.h>
#include <functional>
#include <stdexcept>
#include <string>

#include "clktex.h"

#include "feature.h"
#include "grid.h"
#include "messaging.h"
#include "protomonster.h"
#include "tile.h"

/* monster::monster(const int type, const char family, std::string name, grid
*g) : type(type), family(family), name(name), x(0), y(0), g(g) { meter = 100;
  speed = 10;
} */

monster::monster(protomonster form, enum aitype ait) : protomonster(form) {
  hp = maxhp;
  if (ait < aitype::MAX)
    ai = (aitype)ait;
}

monster::~monster() { g->gettile(x, y)->mon = nullptr; }

int monster::tick() {
  meter -= speed;
  if (meter <= 0) {
    aifuncs[(int)ai](*this);
  }
  return meter;
}

void monster::draw() {
  g->font.drawchar(vports::GRID, x * g->gettilew(), y * g->gettileh(), family);
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

void monster::setx(int newx) { x = newx; }
void monster::sety(int newy) { y = newy; }

std::pair<int, int> monster::move(int newx, int newy) {
  if (g->blocking) {
    meter += 100;
    g->blocking = 0;
    return g->movemonster(this, newx, newy);
  } else
    return std::pair<int, int>(x, y);
}

std::pair<int, int> monster::act(int x, int y) {
  if (g->blocking) {
    if (g->gettile(x, y)->feat && g->gettile(x, y)->feat.get()->fflags) {
      g->gettile(x, y)->feat.get()->act(*this);
      meter += 100;
      g->blocking = 0;
    } else {
      messages::push(
          {"That would be silly.", severitylevel::NORMAL, devlevel::GAME, 0});
    }
  }
  return {0, 0};
}

monster::montrig::montrig(monster &bind) : binding(bind) {}
void monster::montrig::trigger(const SDL_Event &e) { binding.trigger(e); }

void monster::trigger(const SDL_Event &e) {
  std::function<std::pair<int, int>(int, int)> action;

  switch (mode) {
  case monmode::NONE:
    action = [this](int x, int y) { return this->move(x, y); };
    break;
  case monmode::ACTING:
    action = [this](int x, int y) { return this->act(x, y); };
    break;
  }

  messages::push({std::to_string((int)mode)});

  switch (e.key.keysym.sym) {
  case SDLK_ESCAPE:
    mode = monmode::NONE;
    break;
  case SDLK_a:
    mode = monmode::ACTING;
    break;
  case SDLK_KP_7:
    action(x - 1, y - 1);
    break;
  case SDLK_KP_8:
    action(x, y - 1);
    break;
  case SDLK_KP_9:
    action(x + 1, y - 1);
    break;
  case SDLK_KP_4:
    action(x - 1, y);
    break;
  case SDLK_KP_6:
    action(x + 1, y);
    break;
  case SDLK_KP_1:
    action(x - 1, y + 1);
    break;
  case SDLK_KP_2:
    action(x, y + 1);
    break;
  case SDLK_KP_3:
    action(x + 1, y + 1);
    break;
  case SDLK_KP_5:
    action(x, y);
    break;
  }
}

void monster::managerreg(clk::keybind *m) {
  if (manager) {
    messages::push({"Already registered with manager.", severitylevel::DEV,
                    devlevel::DEV, 0});
    return;
  } else
    manager = m;

  for (int i = SDLK_KP_1; i <= SDLK_KP_9; i++)
    manager->registerinput((SDL_Keycode)i, new montrig(*this));
  manager->registerinput(SDLK_a, new montrig(*this));
  manager->registerinput(SDLK_ESCAPE, new montrig(*this));
}

void monster::managerdereg() {
  if (!manager)
    return;
  for (int i = SDLK_KP_1; i <= SDLK_KP_9; i++)
    manager->deregister(i);
}
