// Copyright (c) John Allen Whitley, 2022, BSD 3-Clause

#pragma once

// This is a very basic fixed-width array which can be given an arbitrary size
// at runtime and has access with boundary checking.
// This is meant to be more or less a wrapper around unique_ptr arrays.

#include <memory>
#include <stdexcept>

template <class T> class sdarray {
private:
  std::shared_ptr<T[]> arr;
  const int len;

public:
  sdarray(int size);

  constexpr T &at(int pos);
  constexpr const T &at(int pos) const;

  constexpr T &operator[](int pos);
  constexpr const T &operator[](int pos) const;

  constexpr int size() const noexcept;
  constexpr int max_size() const noexcept;

  constexpr std::shared_ptr<T[]>
  data() noexcept; // This violates the contract a bit since no noexcept.
  constexpr std::shared_ptr<const T[]> data() const noexcept;

  constexpr T &front();
  constexpr const T &front() const;
  constexpr T &back();
  constexpr const T &back() const;

  [[nodiscard]] constexpr bool empty() const noexcept;

  constexpr void swap(sdarray<T> &other);
};

template <class T> sdarray<T>::sdarray(const int size) : len(size) {
  arr.reset(new T[len]);
}

template <class T> constexpr T &sdarray<T>::at(int pos) {
  if (pos < 0 || pos >= len)
    throw std::out_of_range("Reference out of range.");
  else
    return arr[pos];
}

template <class T> constexpr const T &sdarray<T>::at(int pos) const {
  if (pos < 0 || pos >= len)
    throw std::out_of_range("Reference out of range.");
  else
    return arr[pos];
}

template <class T> constexpr T &sdarray<T>::operator[](int pos) {
  return arr[pos];
}

template <class T> constexpr const T &sdarray<T>::operator[](int pos) const {
  return arr[pos];
}

template <class T> constexpr int sdarray<T>::size() const noexcept {
  return len;
}

template <class T> constexpr int sdarray<T>::max_size() const noexcept {
  return len;
}

template <class T> constexpr std::shared_ptr<T[]> sdarray<T>::data() noexcept {
  return std::shared_ptr(arr);
}

template <class T>
constexpr std::shared_ptr<const T[]> sdarray<T>::data() const noexcept {
  return std::shared_ptr(arr);
}

template <class T> constexpr T &sdarray<T>::front() { return arr[0]; }

template <class T> constexpr const T &sdarray<T>::front() const {
  return arr[0];
}

template <class T> constexpr T &sdarray<T>::back() { return arr[len - 1]; }

template <class T> constexpr const T &sdarray<T>::back() const {
  return arr[len - 1];
}

template <class T>
[[nodiscard]] constexpr bool sdarray<T>::empty() const noexcept {
  return arr.get();
}

template <class T> constexpr void sdarray<T>::swap(sdarray<T> &other) {
  if (other.size() != size())
    throw std::out_of_range("Arrays are not of the same size.");

  for (int i = 0; i < size(); i++)
    std::swap(data()[i], other.data()[i]);
}
