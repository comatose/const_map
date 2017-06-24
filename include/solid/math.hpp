#ifndef __SOLID_MATH_HPP
#define __SOLID_MATH_HPP

#include <type_traits>

#include <cstdint>

namespace solid {

constexpr uintmax_t log2(uintmax_t n) {
  uintmax_t r = 0;
  for(; n > 1; n /= 2, ++r) {}
  return r;
}

static_assert(solid::log2(4) == 2);

constexpr uintmax_t pow2(uintmax_t n) {
  uintmax_t r = 1;
  while(n--)
    r *= 2;
  return r;
}

static_assert(solid::pow2(4) == 16);

// constexpr double ceiling()

constexpr uintmax_t nearest_2pow(uintmax_t n) {
  return pow2(log2(n));
}

static_assert(nearest_2pow(15) == 8);

}

#endif // __SOLID_MATH_HPP
