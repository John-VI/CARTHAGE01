// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "clkwin.h"
#include <string>
#include <deque>

enum class devlevel { GAME, DEV };
enum class severitylevel { DEATH, CRITICAL, WARNING, NORMAL, DEV };

namespace clk {
typedef struct sprite sprite;
}

struct message {
  std::string text;
  severitylevel severity;
  devlevel dev;
  unsigned int turn;
};

class messages {
protected:
  std::deque<message> queue;
  devlevel level;
  const clk::window &win;
  const clk::sprite &font;
  unsigned int msgcap = 500;

public:
  messages(const clk::window &window, const clk::sprite &fontface, devlevel level = devlevel::GAME);

  void push(message);

  void draw();
};

