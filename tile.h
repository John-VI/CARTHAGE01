// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

typedef struct monster monster;

class tile {
  monster *mon = nullptr;

 public:
  int type = 0;
};
