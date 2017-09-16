#ifndef __SOLID_STATIC_STRING_HPP
#define __SOLID_STATIC_STRING_HPP

#include "algorithm.hpp"
#include "array.hpp"

namespace solid {

class static_string_view {
 public:
  using const_iterator = const char*;

  template <size_t N>
  constexpr static_string_view(const char (&s)[N])
      : string_(s), length_(N - 1) {}

  constexpr size_t length() const { return length_; }

  constexpr const_iterator begin() const { return &string_[0]; }

  constexpr const_iterator end() const { return &string_[length_]; }

  constexpr const_iterator cbegin() const { return &string_[0]; }

  constexpr const_iterator cend() const { return &string_[length_]; }

 private:
  const char* const string_{};
  const size_t length_{};
};

template <size_t N>
class static_string : public array<char, N + 1> {
  using base_type = array<char, N + 1>;

 public:
  constexpr static_string(const char* s) {
    auto len = find(&s[0], &s[N + 1], '\0') - &s[0];
    assert(len <= N);
    copy(&s[0], &s[len], base_type::begin());
  }
};
}

#endif  // __SOLID_STATIC_STRING_HPP
