// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include "ship.h"

namespace ai {

class spaceinvader : public controller {
protected:
  uint32_t bullettime = 0;
  const static uint32_t bulletthresh = 1000;

public:
  spaceinvader(objectman &objmanager);

  void tick(uint32_t ticks) override;
};

} // namespace ai
