// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

#include <bitset>

#define TILEFLAG_UNDERLYING char
#define TILEFLAG_SIZE sizeof(TILEFLAG_UNDERLYING)

typedef std::bitset<TILEFLAG_SIZE> tflags;

enum class tileflag : TILEFLAG_UNDERLYING {
  PASSABLE = 0b00000001,
  DESTRUCT = 0b00000010,
  TRANSLUC = 0b00000100
};

const inline TILEFLAG_UNDERLYING operator&(tileflag lhs, tileflag rhs);
const inline TILEFLAG_UNDERLYING operator&(TILEFLAG_UNDERLYING lhs, tileflag rhs);
const inline TILEFLAG_UNDERLYING operator|(tileflag lhs, tileflag rhs);
const inline TILEFLAG_UNDERLYING operator|(TILEFLAG_UNDERLYING lhs, tileflag rhs);
