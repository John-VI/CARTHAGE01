// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#define INTWID 640
#define INTHEI 480

#define FONWID 8
#define FONHEI 16

#define MAXFPS 60

#include <SDL2/SDL.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdio.h>

#include "clkinputman.h"
#include "clkkeybind.h"
#include "clkmbuttonbind.h"
#include "clkmenutrig.h"
#include "clkrand.h"
#include "clksheet.h"
#include "clkterminator.h"
#include "clktex.h"
#include "clktiming.h"
#include "clkviewport.h"
#include "clkwin.h"

#include "loopingbg.h"
#include "messaging.h"
#include "objectman.h"
#include "player.h"
#include "ship.h"
#include "spaceinvader.h"

const char *copyright = "Copyright (c) John Allen Whitley, 2022, BSD 3-Clause";

// #define ECHOMAP(MAP)                                                           \
//   for (int i = 0; i < MAP.gety(); i++) {                                       \
//     for (int j = 0; j < MAP.getx(); j++)                                       \
//       printf("%d ", MAP[j + (i * MAP.getx())]);                                \
//     printf("\n");                                                              \
//   }                                                                            \
//  printf("\n\n");

extern "C";

int main(int argc, char *argv[]) {

  const double msecondsperframe = 1000.0 / MAXFPS;

  std::cout << "Starting\n";

  SDL_Color black = {0, 0, 0};

  clk::window win("rusting", INTWID, INTHEI, &black); // We're 100% black
  win.setviewport(vports::FULL, {0, 0, INTWID, INTHEI});
  win.setviewport(vports::RIGHT, {0, 0, 140, INTHEI});
  win.setviewport(vports::LEFT, {500, 0, 140, INTHEI});
  win.setviewport(vports::CENTER, {140, 0, INTWID - 140 * 2, INTHEI});

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

  // clk::mbuttonbind mouse(
  //     *gman.clevel.get(),
  //     iman); // FIXME this is going to break when we change levels
  // mouse.managerreg();

  // double oldangle = 10000;
  // double newangle = 10000;
  // double oldtangle = 0;
  // double newtangle = 0;

  // clk::menubuild menuman(
  //     {                     // {SDLK_c, &mouse.stype},
  //      {SDLK_v, &newangle}, // , {SDLK_b, &mouse.sflag}
  //      {SDLK_c, &newtangle}},
  //     iman, kbd, vga);

  // messages msg(win, vga);

  clk::sprite backgroundasset(win, "testbg1.png");
  loopingbg bg(backgroundasset);
  bg.rate = .05;
  bg.angle = 30;
  bg.travelangle = 0;
  bg.updatepathing();

  clk::sheet shat(win, "01.png",
                  {{0, 0, 62, 32, 1, 1, 0, 0},
                   {67, 0, 10, 24, 1, 1, 0, 0},
                   {79, 0, 12, 12, 1, 1, 0, 0},
                   {91, 0, 66, 17, 1, 1, 0, 0}});

  std::vector<clk::frameinfo> frames{{0, 0, 62, 32, 1, 1, 0, 0},
                                     {67, 0, 10, 24, 1, 1, 0, 0},
                                     {79, 0, 12, 12, 1, 1, 0, 0},
                                     {91, 0, 66, 17, 1, 1, 0, 0}};
  std::vector<hitbox> pboxes{{{-2, 0, 12, 9}}};
  std::vector<hitbox> eboxes{{{0, -4, 66, 6}}, {{0, 3, 42, 11}}};

  objectman objman(hitbox({0, 0, INTWID - 140 * 2, INTHEI}));

  ai::player pai(objman, kbd);
  ai::spaceinvader eai(objman);

  objman.newobject(shiptype::PLAYER, 20, 20, 3, &pboxes,
                   std::make_shared<clk::sheet>(win, "01.png", frames), 0,
                   &pai);

  objman.newobject(shiptype::ENEMY, 50, 50, 100, &eboxes,
                   std::make_shared<clk::sheet>(win, "01.png", frames), 3, &eai,
                   0.2, 0);

  // navmap map1(10, 10);
  // map1[55] = 256;
  // navmap map2(10, 10);
  // map2 = map1.bleedout();
  // ECHOMAP(map1);
  // ECHOMAP(map2);

  clk::timer framedelta;
  framedelta.start();
  Uint32 mseconds = 0;

  while (!terminator) {
    framedelta.start();

    iman.processinputs();

    win.clear();

    // if (accumulator >= 10) {
    //   bg.angle++;
    //   bg.updatepathing();
    //   accumulator -= 10;
    // } else {
    //   accumulator++;
    // }

    // frog.draw(vports::FULL, 0, 0);

    eai.tick(mseconds);

    bg.tick(mseconds);

    objman.tick(mseconds);

    bg.draw();

    objman.draw(win.getviewport(vports::CENTER));

    // vga.drawstring(
    //     vports::STATUS, 96, 0,
    //     std::to_string(gman.clevel.get()->monsters.front().get()->meter));
    // msg.draw();

    win.draw();

    mseconds = framedelta.ticks();

    if ((double)mseconds < msecondsperframe) {
      SDL_Delay((Uint32)(msecondsperframe - mseconds));
      mseconds = framedelta.ticks();
    }
  }
  return 0;
}
