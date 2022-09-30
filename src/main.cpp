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
#include "clktiming.h"
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

  double oldangle = 10000;
  double newangle = 10000;
  double oldtangle = 0;
  double newtangle = 0;

  clk::menubuild menuman(
      {                     // {SDLK_c, &mouse.stype},
       {SDLK_v, &newangle}, // , {SDLK_b, &mouse.sflag}
       {SDLK_c, &newtangle}},
      iman, kbd, vga);

  messages msg(win, vga);

  clk::sprite backgroundasset(win, "testbg1.png");
  loopingbg bg(backgroundasset);
  bg.rate = .05;
  bg.angle = 30;
  bg.travelangle = 0;
  bg.updatepathing();

  clk::timer framedelta;
  framedelta.start();

  while (!terminator) {
    Uint32 mseconds = framedelta.ticks();
    framedelta.start();

    gman.clevel.get()->tick();
    iman.processinputs();

    win.clear();

    if (oldtangle != newtangle) {
      bg.travelangle = newtangle;
      bg.updatepathing();
      oldtangle = newtangle;
    }

    if (oldangle != newangle) {
      bg.angle = newangle;
      bg.updatepathing();
      oldangle = newangle;
    }

    // if (accumulator >= 10) {
    //   bg.angle++;
    //   bg.updatepathing();
    //   accumulator -= 10;
    // } else {
    //   accumulator++;
    // }

    // frog.draw(vports::FULL, 0, 0);
    bg.tick(mseconds);
    bg.draw();

    gman.clevel.get()->draw();
    // vga.drawstring(
    //     vports::STATUS, 96, 0,
    //     std::to_string(gman.clevel.get()->monsters.front().get()->meter));
    msg.draw();

    vga.drawstring(vports::STATUS, 0, 0,
                   "Offset " + std::to_string(bg.currentoffset));
    vga.drawstring(vports::STATUS, 0, 16,
                   "Tr.angle " + std::to_string(bg.travelangle));
    vga.drawstring(vports::STATUS, 150, 0,
                   "Position " + std::to_string(bg.position));
    vga.drawstring(vports::STATUS, 150, 16,
                   "Length " + std::to_string(bg.length));
    vga.drawstring(vports::STATUS, 309, 0, "Angle " + std::to_string(bg.angle));
    vga.drawstring(vports::STATUS, 309, 16,
                   std::to_string(backgroundasset.geth()));

    menuman.draw();

    win.draw();
  }
  return 0;
}
