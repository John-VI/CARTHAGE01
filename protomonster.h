// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <string>
#include <array>
#include <functional>

typedef struct monster monster;

struct protomonster {
	 enum class montype { human, gad, naphtali, MAX };
	 enum class aitype { player, MAX };

	 montype type;
	 char family;
	 short flags;
	 std::string name;
	 int maxhp;
	 int damage;
	 int speed;
   int aitype;
	 char status = 0;

	 static const std::array<protomonster, (int)montype::MAX> kinds;
	 static const std::array<std::function<void(monster &)>, (int)aitype::MAX> aifuncs;

	 virtual monster *genmonster();
};
