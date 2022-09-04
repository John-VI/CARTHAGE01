// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "tileflag.h"

const inline TILEFLAG_UNDERLYING operator&(tileflag lhs, tileflag rhs) {
  return (TILEFLAG_UNDERLYING)lhs & (TILEFLAG_UNDERLYING)rhs;
}

const inline TILEFLAG_UNDERLYING operator&(TILEFLAG_UNDERLYING lhs, tileflag rhs) {
  return lhs & (TILEFLAG_UNDERLYING)rhs;
}

const inline TILEFLAG_UNDERLYING operator|(tileflag lhs, tileflag rhs) {
  return (TILEFLAG_UNDERLYING)lhs & (TILEFLAG_UNDERLYING)rhs;
}

const inline TILEFLAG_UNDERLYING operator|(TILEFLAG_UNDERLYING lhs, tileflag rhs) {
  return lhs & (TILEFLAG_UNDERLYING)rhs;
}
