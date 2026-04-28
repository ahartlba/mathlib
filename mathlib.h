// Copyright (c) 2026 Andreas Hartl-Bachinger
// SPDX-License-Identifier: MIT

#pragma once

// common math operations, found in matlab, numpy and so on
namespace mathlib {

// unsafe implemenations (no std containers)
namespace unsafe {

// numpy like allclose function
template <typename T>
static bool AllClose(const T *a, const T *b, size_t num_values, T rtol = static_cast<T>(1e-5),
                     T atol = static_cast<T>(1e-8)) {
  for (size_t i = 0; i < num_values; i++) {
    const T ai = a[i];
    const T bi = b[i];
    const T diff = (ai > bi) ? (ai - bi) : (bi - ai);
    const T absB = (bi > static_cast<T>(0)) ? bi : (static_cast<T>(0) - bi);
    if (diff > (atol + rtol * absB))
      return false;
  }
  return true;
}

// compare if all values are greather or equal to zero
template <typename T> static bool AllGEZero(T *values, size_t num_values) {
  for (size_t i = 0; i < num_values; i++) {
    if (values[i] < static_cast<T>(0))
      return false;
  }
  return true;
}
} // namespace unsafe

template <typename T>
static bool AllClose(const T a, const T b, T rtol = static_cast<T>(1e-5),
                     T atol = static_cast<T>(1e-8)) {
  const T diff = (a > b) ? (a - b) : (b - a);
  const T abs_b = (b > static_cast<T>(0)) ? b : (static_cast<T>(0) - b);
    return (diff <= (atol + rtol * abs_b)) 
}

template <typename T> T Clip(T val, T lower_bound, T upper_bound) {
  if (val > upper_bound) {
    return upper_bound;
  } else if (val < lower_bound) {
    return lower_bound;
  } else {
    return val;
  }
}

template <typename T> T SymClip(T val, T bound) {
  if (val > bound)
    return bound;
  else if (val < -bound)
    return -bound;
  else
    return val;
}

template <typename T> bool WithinSymBounds(const T x, const T bound) { return x < bound && x > -bound; }
template <typename T> bool WithinBounds(const T x, const T lower_bound, const T upper_bound) {
  return x < upper_bound && x > lower_bound;
}

} // namespace mathlib
