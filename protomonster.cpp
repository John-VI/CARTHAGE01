// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "protomonster.h"

#include <string>
#include <array>
#include <functional>

#include "monster.h"
#include "grid.h"

monster *protomonster::genmonster() {
  return new monster(*this);
}

/* === MONSTER DEFINITIONS === */

const std::array<protomonster, (int)protomonster::montype::MAX> protomonster::kinds {{
  { montype::human, '@', 0, "human", 100, 10, 10, 0 },
    { montype::gad, 'a', 0, "gad", 80, 10, 10, 0 },
    { montype::naphtali, 'D', 0, "naphtali", 120, 15, 10, 0}
}};

const std::array<std::function<void(monster &)>, (int)protomonster::aitype::MAX> protomonster::aifuncs {{
[] (monster &m) { m.g->blocking = 1; }
}};
