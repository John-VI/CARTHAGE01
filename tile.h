// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

typedef struct monster monster;

struct tile {
  monster *mon = nullptr;
  int type = 0;
};
