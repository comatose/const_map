#ifndef __SOLID_ARRAY_HPP
#define __SOLID_ARRAY_HPP

#include <algorithm>
#include <cstddef>

namespace solid {

template<typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using iterator = T*;
  using const_iterator = const T*;

  constexpr array() = default;

  constexpr array(const array& other)
  : array(other.cbegin(), other.cend()) {
  }

  template<class InputIt>
  constexpr array(InputIt first, InputIt last) {
    copy(first, last, begin());
  }

  constexpr array(std::initializer_list<T> init) {
    copy(init.begin(), init.end(), begin());
  }

  constexpr std::size_t size() const {
    return N;
  }

  constexpr T& operator[](std::size_t i) {
    return elements_[i];
  }

  constexpr const T& operator[](std::size_t i) const {
    return elements_[i];
  }

  constexpr iterator begin() {
    return &elements_[0];
  }

  constexpr iterator end() {
    return &elements_[N];
  }

  constexpr const_iterator begin() const {
    return &elements_[0];
  }

  constexpr const_iterator end() const {
    return &elements_[N];
  }

  constexpr const_iterator cbegin() const {
    return &elements_[0];
  }

  constexpr const_iterator cend() const {
    return &elements_[N];
  }

 private:
  T elements_[N]{};
};

template<typename T, std::size_t N>
constexpr array<T, N+1> append(const array<T, N>& a, T v) {
  array<T, N+1> r{a.begin(), a.end()};
  r[N] = std::move(v);
  return r;
}

}

namespace std {

template<class T, size_t N>
struct tuple_size<solid::array<T, N>> : integral_constant<size_t, N>
{};

}
#endif // __SOLID_ARRAY_HPP
