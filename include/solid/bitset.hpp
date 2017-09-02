#pragma once

#include <cstddef>

#include "math.hpp"

namespace solid {
template <std::size_t N>
class bitset {
  static constexpr auto BITS_PER_UINT = sizeof(unsigned int) * 8;

 public:
  constexpr bitset() = default;

  constexpr std::size_t size() const { return N; }

  constexpr void set(std::size_t i) {
    assert(i < N);
    if (test(i)) return;

    ++count_;
    storage_[i / BITS_PER_UINT] |= 1U << (i % BITS_PER_UINT);
  }

  constexpr void reset(std::size_t i) {
    assert(i < N);
    if (!test(i)) return;

    --count_;
    storage_[i / BITS_PER_UINT] &= ~(1U << (i % BITS_PER_UINT));
  }

  constexpr bool test(std::size_t i) const {
    assert(i < N);

    return storage_[i / BITS_PER_UINT] & (1U << (i % BITS_PER_UINT));
  }

  constexpr std::size_t count() const { return count_; }

 private:
  unsigned int storage_[align_up(N, BITS_PER_UINT) / BITS_PER_UINT]{};
  std::size_t count_{0};
};
}
