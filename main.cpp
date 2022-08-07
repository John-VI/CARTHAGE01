// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include <cassert>
#define INTWID 480
#define INTHEI 416

#define FONWID 8
#define FONHEI 16

#include <fstream>
#include <iostream>
#include <memory>

#include "clkinputman.h"
#include "clkkeybind.h"
#include "clkmbuttonbind.h"
#include "clkmenutrig.h"
#include "clkterminator.h"
#include "clktex.h"
#include "clkviewport.h"
#include "clkwin.h"

#include "clf1.h"
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

  grid g2(15, 15, 8, 16,
          vga); // FIXME: Oopsie, I jacked up the grid for testing!

  std::fstream levelfile;
  levelfile.open("testio.clf1", std::ios::in | std::ios::out |
                                    std::ios::binary | std::ios::trunc);
  assert(levelfile.is_open());
  clf1::encode(levelfile, g2);
  levelfile.clear();
  levelfile.seekg(0);
  grid g = clf1::decode(levelfile, 8, 16, vga);

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

  clk::mbuttonbind mouse(g, iman);
  mouse.managerreg();

  clk::menubuild menuman(
      {{SDLK_c, &mouse.stype}, {SDLK_v, &mouse.sflag}, {SDLK_b, &mouse.sflag}},
      iman, kbd, vga);

  messages msg(win, vga);

  while (!terminator) {
    g.tick();
    iman.processinputs();

    win.clear();
    frog.draw(vports::FULL, 0, 0);
    g.draw();
    vga.drawstring(vports::STATUS, 96, 0,
                   std::to_string(g.monsters.front().get()->meter));
    msg.draw();
    vga.drawstring(vports::STATUS, 0, 0, std::to_string(mouse.stype));
    vga.drawstring(vports::STATUS, 32, 0, std::to_string(mouse.sfeat));
    vga.drawstring(vports::STATUS, 64, 0, std::to_string(mouse.sflag));
    menuman.draw();

    win.draw();
  }
  return 0;
}
