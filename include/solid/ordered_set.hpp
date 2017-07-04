#ifndef __SOLID_ORDERED_SET_HPP
#define __SOLID_ORDERED_SET_HPP

#include "array.hpp"
#include "algorithm.hpp"

#include <initializer_list>

namespace solid {

template<typename T, std::size_t N>
class ordered_set {
 public:
  using value_type = T;
  using const_iterator = const T*;

  constexpr ordered_set(std::initializer_list<T> init)
  : elements_(init) {
    quick_sort(elements_.begin(), elements_.end());
  }

  constexpr bool contains(const T& k) const {
    return binary_search(begin(), end(), k) != end();
  }

  constexpr const_iterator begin() const {
    return elements_.begin();
  }

  constexpr const_iterator end() const {
    return elements_.end();
  }

  constexpr const_iterator cbegin() const {
    return elements_.cbegin();
  }

  constexpr const_iterator cend() const {
    return elements_.cend();
  }

 private:
  array<T, N> elements_{};
};

}
#endif // __SOLID_ORDERED_SET_HPP
