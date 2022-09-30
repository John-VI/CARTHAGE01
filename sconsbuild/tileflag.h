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

/* inline TILEFLAG_UNDERLYING operator&(tileflag lhs, tileflag rhs); */
/* inline TILEFLAG_UNDERLYING operator&(TILEFLAG_UNDERLYING lhs, tileflag rhs);
 */
/* inline TILEFLAG_UNDERLYING operator|(tileflag lhs, tileflag rhs); */
/* inline TILEFLAG_UNDERLYING operator|(TILEFLAG_UNDERLYING lhs, tileflag rhs);
 */

inline TILEFLAG_UNDERLYING operator&(tileflag lhs, const tileflag rhs) {
  return (TILEFLAG_UNDERLYING)lhs & (TILEFLAG_UNDERLYING)rhs;
}

inline TILEFLAG_UNDERLYING operator&(TILEFLAG_UNDERLYING lhs,
                                     const tileflag rhs) {
  return lhs & (TILEFLAG_UNDERLYING)rhs;
}

inline TILEFLAG_UNDERLYING operator|(tileflag lhs, const tileflag rhs) {
  return (TILEFLAG_UNDERLYING)lhs | (TILEFLAG_UNDERLYING)rhs;
}

inline TILEFLAG_UNDERLYING operator|(TILEFLAG_UNDERLYING lhs,
                                     const tileflag rhs) {
  return lhs | (TILEFLAG_UNDERLYING)rhs;
}

inline tflags operator&(tflags lhs, tileflag rhs) {
  return lhs & (tflags)(char)rhs; // C++ typing is weird
}

inline tflags operator|(tflags lhs, tileflag rhs) {
  return lhs | (tflags)(char)rhs;
}

inline bool compbit(tflags bits, tileflag flag) {
  return bits.to_ulong() & flag;
}
