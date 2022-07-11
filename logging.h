// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "clkwin.h"
#include <string>
#include <vector>

enum class messagelevel { GAME, DEV };
enum class severitylevel { DEATH, CRITICAL, WARNING, NORMAL, DEV };

struct message {
  message();
  message(std::string, severitylevel, unsigned int);
  std::string text;
  severitylevel severity;
  unsigned int turn;
};

class messages {
protected:
  std::vector<message> queue;
  messagelevel level = messagelevel::DEV;
  clk::window &win;
};
