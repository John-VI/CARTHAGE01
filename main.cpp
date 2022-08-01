// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#define INTWID 480
#define INTHEI 416

#define FONWID 8
#define FONHEI 16

#include <iostream>
#include <memory>

#include "clkinputman.h"
#include "clkkeybind.h"
#include "clkmenutrig.h"
#include "clkterminator.h"
#include "clktex.h"
#include "clkviewport.h"
#include "clkwin.h"
#include "grid.h"
#include "messaging.h"
#include "monster.h"

const char *copyright = "Copyright (c) John Allen Whitley, 2022, BSD 3-Clause";

int main(int argc, char *argv[]) {
  std::cout << "Starting\n";

  SDL_Color black = {0, 0, 0};

  clk::window win("rusting", INTWID, INTHEI, &black); // We're 100% black
  win.setviewport(vports::FULL, {0, 0, INTWID, INTHEI});
  win.setviewport(vports::GRID, {0, 0, 40 * FONWID, 24 * FONHEI});
  win.setviewport(vports::MESSAGES, {40 * FONWID, 0, 20 * FONWID, 26 * FONHEI});
  win.setviewport(vports::STATUS, {0, 24 * FONHEI, 40 * FONWID, 2 * FONHEI});

  clk::sprite frog(win, "frog.png");
  clk::sprite vga(win, "compac.png");
  vga.setsheetoffset({0, 0, 8, 16});
  vga.setscreenoffset({0, 0, 8, 16});

  grid g(15, 15, 8, 16, vga);

  clk::inputman iman;

  int terminator = 0;
  clk::terminator quitter(terminator);
  quitter.managerreg(&iman);

  clk::keybind kbd;
  kbd.managerreg(&iman);

  std::unique_ptr<monster> m =
      std::make_unique<monster>(0, '@', std::string("You"), &g);
  m->managerreg(&kbd);
  g.insertmonster(std::move(m));

  char value = 0;

  clk::menubuild menuman({{SDLK_c, &value}}, iman, kbd, vga);

  messages msg(win, vga);

  while (!terminator) {
    g.tick();
    iman.processinputs();

    win.clear();
    frog.draw(vports::FULL, 0, 0);
    g.draw();
    vga.drawstring(vports::STATUS, 0, 0,
                   std::to_string(g.monsters.front().get()->meter));
    msg.draw();
    vga.drawstring(vports::STATUS, 20, 0, std::to_string(value));
    menuman.draw();

    win.draw();
  }
  return 0;
}
