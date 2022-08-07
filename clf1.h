// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <sstream>

namespace clk {
typedef struct sprite sprite;
}
typedef struct grid grid;

namespace clf1 {

grid decode(std::istream &level, int fonwid, int fonhei, clk::sprite &font);
long encode(std::ostream &level, const grid &g);

} // namespace clf1
