#ifndef __SOLID_MATH_HPP
#define __SOLID_MATH_HPP

#include <cstdint>

#include <type_traits>

namespace solid {

constexpr uintmax_t log2(uintmax_t n) {
  assert(n != 0);

  uintmax_t r = 0;
  for (; n > 1; n /= 2, ++r) {
  }
  return r;
}

static_assert(solid::log2(4) == 2);

constexpr uintmax_t pow2(uintmax_t n) {
  assert(sizeof(uintmax_t) / sizeof(uint8_t) * 8 > n);

  uintmax_t r = 1;
  while (n--) r *= 2;
  return r;
}

static_assert(solid::pow2(63) == 0x8000000000000000);

// constexpr double ceiling()

constexpr uintmax_t nearest_2pow(uintmax_t n) { return pow2(log2(n)); }

static_assert(nearest_2pow(15) == 8);

constexpr uintmax_t align_up(uintmax_t n, uintmax_t a) {
  return (n + a - 1) / a * a;
}

static_assert(align_up(11, 5) == 15);
static_assert(align_up(15, 5) == 15);
static_assert(align_up(14, 5) == 15);
}  // namespace solid

#endif  // __SOLID_MATH_HPP
