#ifndef __SOLID_ORDERED_SET_HPP
#define __SOLID_ORDERED_SET_HPP

#include <initializer_list>
#include <iterator>
#include <type_traits>

#include "algorithm.hpp"
#include "array.hpp"

namespace solid {

template <typename T, std::size_t N, class Compare = less<T>>
class ordered_set {
 public:
  using value_type = T;
  using const_iterator = const T*;

  constexpr ordered_set(std::initializer_list<T> init)
      : ordered_set(init.begin(), init.end()) {}

  template <class Ts>
  constexpr ordered_set(const Ts& ts)
      : ordered_set{std::begin(ts), std::end(ts)} {}

  template <class InputIt>
  constexpr ordered_set(InputIt first, InputIt last)
      : elements_((assert(first <= last && last - first == N), first), last) {
    static_assert(
        std::is_same<
            std::decay_t<typename std::iterator_traits<InputIt>::value_type>,
            T>::value);

    quick_sort(elements_.begin(), elements_.end(), Compare{});
  }

  constexpr std::size_t size() const { return N; }

  constexpr bool contains(const T& k) const {
    return binary_search(begin(), end(), k, Compare{}) != end();
  }

  constexpr const_iterator begin() const { return elements_.begin(); }

  constexpr const_iterator end() const { return elements_.end(); }

  constexpr const_iterator cbegin() const { return elements_.cbegin(); }

  constexpr const_iterator cend() const { return elements_.cend(); }

 private:
  array<T, N> elements_;
  Compare compare_;
};

template <typename T, size_t N, class Compare = less<T>>
constexpr ordered_set<T, N, Compare> make_ordered_set(
    const T (&ar)[N], const Compare& = Compare{}) {
  return {ar};
}
}
#endif  // __SOLID_ORDERED_SET_HPP
