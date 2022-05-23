// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkinputman.h"

#include <stdexcept>

#include <SDL2/SDL_events.h>

clk::inputman::inputman(inputmap &smap) : sharedmap(smap){};

int clk::inputman::processinputs() {
  int i = 0;
  SDL_Event e;

  while (SDL_PollEvent(&e)) {
    try {
      std::list<std::unique_ptr<clkinputtrigger>> &registered =
          imap.at((SDL_EventType)e.type).second;
      for (auto &t : registered)
        t->trigger(e);
      i++;
    } catch (std::out_of_range) {
    }
    try {
      std::list<std::unique_ptr<clkinputtrigger>> &registered =
          imap.at((SDL_EventType)e.type).second;
      for (auto &t : registered)
        t->trigger(e);
      i++;
    } catch (std::out_of_range) {
    }
  }
  return i;
}

int clk::inputman::registerinput(SDL_EventType type,
                                 std::unique_ptr<clkinputtrigger> newtrigger) {
  newtrigger->id = ++imap[type].first;
  imap[type].second.push_back(newtrigger);
  return newtrigger->id;
}

void clk::inputman::deregister(SDL_EventType type, int id) {
  for (auto &t : imap.at(type).second)
    if (t->id == id) {
      imap.at(type).second.remove(t);
      break;
    }
}