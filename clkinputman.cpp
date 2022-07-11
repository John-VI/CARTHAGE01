// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkinputman.h"

#include <stdexcept>

#include <SDL2/SDL_events.h>

clk::inputman::inputman() = default;

int clk::inputman::processinputs() {
  int i = 0;
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    std::list<std::unique_ptr<inputtrigger>> *registered = nullptr;
    try {
      registered = &imap.at((SDL_EventType)e.type).second;
    } catch (std::out_of_range) {
    }
    if (registered) {
      for (auto &t : *registered)
        t->trigger(e);
      i++;
      registered = nullptr;
    }
  }
  return i;
}

int clk::inputman::registerinput(SDL_EventType type,
                                 std::unique_ptr<inputtrigger> newtrigger) {
  int id = ++imap[type].first;
  newtrigger->id = id;
  imap[type].second.push_back(std::move(newtrigger));
  return id;
}

void clk::inputman::deregister(SDL_EventType type, int id) {
  for (auto &t : imap.at(type).second)
    if (t->id == id) {
      imap.at(type).second.remove(t);
      break;
    }
}