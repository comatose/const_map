#ifndef __SOLID_STATIC_STRING_HPP
#define __SOLID_STATIC_STRING_HPP

#include "algorithm.hpp"
#include "array.hpp"

namespace solid {

class static_string_view {
 public:
  using value_type = char;
  using const_iterator = const char*;

  constexpr static_string_view() = default;
  constexpr static_string_view(const static_string_view&) = default;
  constexpr static_string_view& operator=(const static_string_view&) = default;

  template <size_t N>
  constexpr static_string_view(const char (&s)[N])
      : string_(s), length_(N - 1) {}

  constexpr size_t length() const { return length_; }

  constexpr const_iterator begin() const { return &string_[0]; }

  constexpr const_iterator end() const { return &string_[length_]; }

  constexpr const_iterator cbegin() const { return &string_[0]; }

  constexpr const_iterator cend() const { return &string_[length_]; }

  constexpr const value_type& operator[](std::size_t i) const {
    assert(i < length_);
    return string_[i];
  }

  friend constexpr bool operator==(const static_string_view& lhs,
                                   const static_string_view& rhs) {
    if (lhs.length_ != rhs.length_) return false;

    for (auto i = 0U; i < lhs.length_; ++i) {
      if (lhs[i] != rhs[i]) return false;
    }
    return true;
  }

 private:
  const char* string_{};
  size_t length_{};
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

template <>
struct hash<static_string_view> {
  constexpr std::size_t operator()(const static_string_view& s) const {
    std::size_t value = 14695981039346656037U;
    for (auto c : s) {
      value = (value ^ c) * 1099511628211U;
    }
    return value;
  }
};
}

#endif  // __SOLID_STATIC_STRING_HPP
