// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#include "sdarray.h"

template <class T> sdarray<T>::sdarray(const int size) : len(size) {
  arr(new T[len]);
}
