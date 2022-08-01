// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "grid.h"

#include "clktex.h"

#include <sstream>

namespace clf1 {

grid decode(std::istream &level, int fonwid, int fonhei, clk::sprite &font);

}
