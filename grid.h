// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

class grid {
  int w;
  int h;
  std::forward_list<std::unique_ptr<monster>> monsters;
};

