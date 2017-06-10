#ifndef __SOLID_UNORDERED_SET_HPP
#define __SOLID_UNORDERED_SET_HPP

#include "algorithm.hpp"
#include "array.hpp"

#include <cstddef>
#include <initializer_list>

namespace solid {

template<typename Key, std::size_t N>
class unordered_set : public array<Key, N> {
  using base_type = array<Key, N>;
 public:
  using iterator = Key*;
  using const_iterator = const Key*;

  using base_type::begin;
  using base_type::end;
  using base_type::cbegin;
  using base_type::cend;
  using base_type::size;
  using base_type::operator[];

  constexpr unordered_set() = default;

  constexpr unordered_set(const unordered_set& other)
  : base_type(other) {
  }

  template<class InputIt>
  constexpr unordered_set(InputIt first, InputIt last)
  : base_type(first, last) {
    quick_sort(begin(), end());
  }

  constexpr unordered_set(std::initializer_list<Key> init)
  : base_type(init) {
    quick_sort(begin(), end());
  }

  constexpr iterator find(const Key& k) {
    return binary_search(begin(), end(), k);
  }

  constexpr const_iterator find(const Key& k) const {
    return binary_search(cbegin(), cend(), k);
  }
};

}
#endif // __SOLID_UNORDERED_SET_HPP
