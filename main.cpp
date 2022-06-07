// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#define INTWID 480
#define INTHEI 416

#include <memory>
#include <iostream>

#include "clkinputman.h"
#include "clktex.h"
#include "clkwin.h"
#include "grid.h"
#include "clkterminator.h"
#include "clkkeybind.h"
#include "monster.h"

const char *copyright = "Copyright (c) John Allen Whitley, 2022, BSD 3-Clause";

int main(int argc, char *argv[]) {
  std::cout << "Starting\n";
  SDL_Color white = {255, 255, 255};
  SDL_Rect viewport = {0, 0, INTWID, INTHEI};

  clk::window win("rusting", INTWID, INTHEI, &white);
  clk::sprite frog(win, "frog.png", &viewport);
  clk::sprite vga(win, "compac.png", &viewport);

  grid g(15, 15, 8, 16, vga);

  clk::inputman iman;

  int terminator = 0;
  clk::terminator quitter(terminator);
  quitter.managerreg(&iman);

  clk::keybind kbd;
  kbd.managerreg(&iman);

  std::unique_ptr<monster> m = std::make_unique<monster>(0, '@', std::string("You"), &g);
  m->managerreg(&kbd);
  g.insertmonster(std::move(m));

  while (!terminator) {
    g.tick();
    iman.processinputs();

    frog.draw(0, 0);
    g.draw();
  }
  return 0;
}