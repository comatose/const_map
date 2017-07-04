#ifndef __SOLID_ORDERED_MAP_HPP
#define __SOLID_ORDERED_MAP_HPP

#include "array.hpp"
#include "ordered_set.hpp"
#include "pair.hpp"

#include <algorithm>
#include <cstddef>
#include <initializer_list>

namespace solid {

template<typename Key, typename Value, std::size_t N>
class ordered_map {
  struct key_comparer {
    template<class P>
    constexpr bool operator()(const P& lhs, const P& rhs) {
      return lhs.first < rhs.first;
    }
  };

 public:
  using value_type = pair<Key, Value>;
  using const_iterator = const value_type*;

  constexpr ordered_map() = default;

  constexpr ordered_map(std::initializer_list<value_type> init)
  : elements_{init} {
    quick_sort(elements_.begin(), elements_.end(), key_comparer{});
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

  constexpr const Value& operator[](const Key& key) const {
    auto it = find(key);
    assert(it != cend());

    return it->second;
  }

  constexpr const_iterator find(const Key& k) const {
    return binary_search(elements_.begin(), elements_.end(), value_type{k, Value{}}, key_comparer{});
  }

 private:
  array<value_type, N> elements_{};
};

}
#endif // __SOLID_ORDERED_MAP_HPP
