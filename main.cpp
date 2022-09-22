// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#define INTWID 480
#define INTHEI 416

#define FONWID 8
#define FONHEI 16

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>

#include "clkinputman.h"
#include "clkkeybind.h"
#include "clkmbuttonbind.h"
#include "clkmenutrig.h"
#include "clkrand.h"
#include "clkterminator.h"
#include "clktex.h"
#include "clkviewport.h"
#include "clkwin.h"

#include "clf1.h"
#include "door.h"
#include "grid.h"
#include "gridman.h"
#include "loopingbg.h"
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

  clk::inputman iman;

  int terminator = 0;
  clk::terminator quitter(terminator);
  quitter.managerreg(&iman);

  clk::keybind kbd;
  kbd.managerreg(&iman);

  clk::randctl::randinit();

  gridman gman(vga, kbd);
  gman.load();
  gman.managerreg();

  gman.clevel.get()->gettile(5, 5)->mkfeat<door>();

  clk::mbuttonbind mouse(
      *gman.clevel.get(),
      iman); // FIXME this is going to break when we change levels
  mouse.managerreg();

  double oldangle = 0;
  double newangle = 0;

  clk::menubuild menuman(
      {
          // {SDLK_c, &mouse.stype},
          {SDLK_v, &newangle} // , {SDLK_b, &mouse.sflag}
      },
      iman, kbd, vga);

  messages msg(win, vga);

  clk::sprite backgroundasset(win, "testbg1.png");
  loopingbg bg(backgroundasset);
  bg.rate = 2;
  bg.travelangle = newangle;
  bg.updatepathing();

  while (!terminator) {
    gman.clevel.get()->tick();
    iman.processinputs();

    win.clear();

    if (oldangle != newangle) {
      bg.travelangle = newangle;
      bg.updatepathing();
      oldangle = newangle;
    }

    // frog.draw(vports::FULL, 0, 0);
    bg.tick(1);
    bg.draw();

    gman.clevel.get()->draw();
    // vga.drawstring(
    //     vports::STATUS, 96, 0,
    //     std::to_string(gman.clevel.get()->monsters.front().get()->meter));
    msg.draw();

    vga.drawstring(vports::STATUS, 0, 0, std::to_string(bg.currentoffset));
    vga.drawstring(vports::STATUS, 0, 16, std::to_string(bg.travelangle));
    vga.drawstring(vports::STATUS, 100, 0, std::to_string(bg.position));
    vga.drawstring(vports::STATUS, 100, 16, std::to_string(bg.length));
    vga.drawstring(vports::STATUS, 200, 0,
                   std::to_string(backgroundasset.getw()));
    vga.drawstring(vports::STATUS, 200, 16,
                   std::to_string(backgroundasset.geth()));

    menuman.draw();

    win.draw();
  }
  return 0;
}
