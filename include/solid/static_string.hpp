#ifndef __SOLID_STATIC_STRING_HPP
#define __SOLID_STATIC_STRING_HPP

#include "algorithm.hpp"
#include "array.hpp"

namespace solid {

template <size_t N>
class static_string : public array<char, N> {
  using base_type = array<char, N>;

 public:
  constexpr static_string(const char* s) {
    auto len = find(&s[0], &s[N], '\0') - &s[0];
    assert(len < N);
    copy(&s[0], &s[len], base_type::begin());
  }
};

class static_string_view {
 public:
  template <size_t N>
  constexpr static_string_view(const char (&s)[N]) : string_(s), size_(N) {}

 private:
  const char* const string_{};
  size_t size_{};
};
}

#endif  // __SOLID_STATIC_STRING_HPP
