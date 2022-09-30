// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "protomonster.h"

#include <array>
#include <functional>
#include <string>

#include "grid.h"
#include "monster.h"

protomonster::protomonster(montype type, char family, short flags,
                           std::string name, int maxhp, int damage, int speed,
                           aitype ai, char status)
    : type(type), family(family), flags(flags), name(name), maxhp(maxhp),
      damage(damage), speed(speed), ai(ai), status(status){};

monster *protomonster::genmonster() const { return new monster(*this); }

/* === MONSTER DEFINITIONS === */

const std::array<protomonster, (int)protomonster::montype::MAX>
    protomonster::kinds{
        {{montype::human, '@', 0, "human", 100, 10, 10, aitype::player, 0},
         {montype::gad, 'a', 0, "gad", 80, 10, 10, aitype::player, 0},
         {montype::naphtali, 'D', 0, "naphtali", 120, 15, 10, aitype::player,
          0}}};

const std::array<std::function<void(monster &)>, (int)protomonster::aitype::MAX>
    protomonster::aifuncs{{[](monster &m) { m.g->blocking = 1; }}};
