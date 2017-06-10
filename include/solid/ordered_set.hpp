#ifndef __SOLID_ORDERED_SET_HPP
#define __SOLID_ORDERED_SET_HPP

#include "array.hpp"
#include "algorithm.hpp"

#include <initializer_list>

namespace solid {

template<typename Key, std::size_t N>
class ordered_set : public array<Key, N> {
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

  constexpr ordered_set() = default;

  constexpr ordered_set(const ordered_set& other)
  : base_type(other) {
  }

  template<class InputIt>
  constexpr ordered_set(InputIt first, InputIt last)
  : base_type(first, last) {
    quick_sort(begin(), end());
  }

  constexpr ordered_set(std::initializer_list<Key> init)
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
#endif // __SOLID_ORDERED_SET_HPP
