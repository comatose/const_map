#ifndef __SOLID_ARRAY_HPP
#define __SOLID_ARRAY_HPP

#include <cassert>
#include <cstddef>

#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>

namespace solid {

template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using iterator = T*;
  using const_iterator = const T*;

  constexpr array() = default;

  constexpr array(const array& other) : array(other.cbegin(), other.cend()) {}

  constexpr array(std::initializer_list<T> init)
      : array{init.begin(), init.end()} {}

  template <class Ts>
  constexpr array(const Ts& ts) : array{std::begin(ts), std::end(ts)} {}

  template <class InputIt>
  constexpr array(InputIt first, InputIt last) {
    static_assert(
        std::is_same<
            std::decay_t<typename std::iterator_traits<InputIt>::value_type>,
            T>::value);
    assert(first <= last);
    assert(last - first <= N);
    copy(first, last, begin());
  }

  constexpr std::size_t size() const { return N; }

  constexpr T& operator[](std::size_t i) {
    assert(i < N);
    return elements_[i];
  }

  constexpr const T& operator[](std::size_t i) const {
    assert(i < N);
    return elements_[i];
  }

  constexpr iterator begin() { return &elements_[0]; }

  constexpr iterator end() { return &elements_[N]; }

  constexpr const_iterator begin() const { return &elements_[0]; }

  constexpr const_iterator end() const { return &elements_[N]; }

  constexpr const_iterator cbegin() const { return &elements_[0]; }

  constexpr const_iterator cend() const { return &elements_[N]; }

 private:
  T elements_[N]{};
};

template <typename T, size_t N>
constexpr array<T, N + 1> append(const array<T, N>& a, T&& v) {
  array<T, N + 1> r{a.begin(), a.end()};
  r[N] = std::forward<T>(v);
  return r;
}

template <typename T, size_t N>
constexpr array<T, N> make_array(const T (&ar)[N]) {
  return {&ar[0], &ar[N]};
}
}

namespace std {

template <class T, size_t N>
struct tuple_size<solid::array<T, N>> : integral_constant<size_t, N> {};
}
#endif  // __SOLID_ARRAY_HPP
