// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#define INTWID 480
#define INTHEI 416

#include "clkinputman.h"
#include "clktex.h"
#include "clkwin.h"
#include "grid.h"
#include "clkterminator.h"
#include "clkkeybind.h"

char *copyright = "Copyright (c) John Allen Whitley, 2022, BSD 3-Clause";

int main(int argc, char *argv[]) {
  SDL_Color white = {255, 255, 255};
  SDL_Rect viewport = {0, 0, INTWID, INTHEI};

  clk::window win("rusting", INTWID, INTHEI, &white);
  clk::sprite frog(win, "frog.png", &viewport);
  clk::sprite vga(win, "compac.png", &viewport);

  grid g(15, 15, 8, 16, vga);
  clk::inputman iman();

  int terminator = 0;
  clk::terminator quitter(terminator);

  clk::keybind kbd();


}