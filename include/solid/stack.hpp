#ifndef __SOLID_STACK_HPP
#define __SOLID_STACK_HPP

#include <algorithm>
#include <cstddef>

namespace solid {

template<typename T, std::size_t N>
class stack {
 public:
  using iterator = T*;
  using const_iterator = const T*;

  constexpr stack() = default;

  constexpr stack(const stack& other)
  : stack(other.cbegin(), other.cend()) {
  }

  template<class InputIt>
  constexpr stack(InputIt first, InputIt last) {
    copy(first, last, begin());
    size_ = last - first;
  }

  constexpr stack(std::initializer_list<T> init)
      : stack(init.begin(), init.end()) {
  }

  constexpr std::size_t capacity() const {
    return N;
  }

  constexpr std::size_t size() const {
    return size_;
  }

  constexpr iterator begin() {
    return &elements_[0];
  }

  constexpr iterator end() {
    return &elements_[size_];
  }

  constexpr const_iterator begin() const {
    return &elements_[0];
  }

  constexpr const_iterator end() const {
    return &elements_[size_];
  }

  constexpr const_iterator cbegin() const {
    return &elements_[0];
  }

  constexpr const_iterator cend() const {
    return &elements_[size_];
  }

  constexpr void push(T v) {
    elements_[size_++] = std::move(v);
  }

  constexpr T pop() {
    return std::move(elements_[--size_]);
  }

  constexpr T& top() {
    return elements_[size_ - 1];
  }

 private:
  T elements_[N]{};
  std::size_t size_{0};
};

template<typename T, std::size_t N>
constexpr stack<T, N+1> append(const stack<T, N>& a, T v) {
  stack<T, N+1> r{a.begin(), a.end()};
  r[N] = std::move(v);
  return r;
}

}

namespace std {

template<class T, size_t N>
struct tuple_size<solid::stack<T, N>> : integral_constant<size_t, N>
{};

}
#endif // __SOLID_STACK_HPP
