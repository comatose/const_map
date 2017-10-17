#ifndef __SOLID_LENS_HPP
#define __SOLID_LENS_HPP

#include <utility>

namespace solid {

template <typename T, class F>
class lens {
 public:
  using value_type = decltype(std::declval<F>()(*std::declval<T>()));

  constexpr lens(T iterator, F f) : iterator_(iterator), fun_(f) {}

  constexpr const lens& operator++() {
    ++iterator_;
    return *this;
  }

  constexpr bool operator!=(const lens& other) const {
    return iterator_ != other.iterator_;
  }

  constexpr bool operator<(const lens& other) const {
    return iterator_ < other.iterator_;
  }

  constexpr bool operator>(const lens& other) const {
    return iterator_ > other.iterator_;
  }

  constexpr bool operator<=(const lens& other) const {
    return iterator_ <= other.iterator_;
  }

  constexpr bool operator>=(const lens& other) const {
    return iterator_ >= other.iterator_;
  }

  constexpr bool operator==(const lens& other) const {
    return iterator_ == other.iterator_;
  }

  constexpr bool operator-(const lens& other) const {
    return iterator_ - other.iterator_;
  }

  constexpr value_type operator*() const { return fun_(*iterator_); }

 private:
  T iterator_;
  F fun_;
};

template <typename T, class F>
constexpr lens<T, F> make_lens(T it, F f) {
  return {it, f};
}
}  // namespace solid

namespace std {
template <typename T, class F>
struct iterator_traits<solid::lens<T, F>> {
  using value_type = typename solid::lens<T, F>::value_type;
};
}  // namespace std
#endif  // __SOLID_LENS_HPP
