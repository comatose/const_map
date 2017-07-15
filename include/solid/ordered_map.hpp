#ifndef __SOLID_ORDERED_MAP_HPP
#define __SOLID_ORDERED_MAP_HPP

#include <cstddef>

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <type_traits>

#include "array.hpp"
#include "ordered_set.hpp"
#include "pair.hpp"

namespace solid {

template <typename Key, class Compare = less<Key>>
struct key_compare {
  template <class P>
  constexpr bool operator()(const P& lhs, const P& rhs) {
    return Compare{}(lhs.first, rhs.first);
  }
};

template <typename Key, typename Value, std::size_t N,
          class Compare = less<Key>>
class ordered_map
    : protected ordered_set<pair<Key, Value>, N, key_compare<Key, Compare>> {
  using key_compare = key_compare<Key, Compare>;
  using base_type = ordered_set<pair<Key, Value>, N, key_compare>;

 public:
  using value_type = pair<Key, Value>;
  using const_iterator = const value_type*;

  using base_type::base_type;
  using base_type::size;
  using base_type::begin;
  using base_type::end;
  using base_type::cbegin;
  using base_type::cend;

  constexpr const Value& operator[](const Key& key) const {
    auto it = find(key);
    assert(it != cend());

    return it->second;
  }

  constexpr const_iterator find(const Key& k) const {
    return binary_search(base_type::elements_.begin(),
                         base_type::elements_.end(), value_type{k, Value{}},
                         key_compare{});
  }
};

template <typename Key, typename Value, size_t N, class Compare = less<Key>>
constexpr ordered_map<Key, Value, N, Compare> make_ordered_map(
    const pair<Key, Value> (&ar)[N], const Compare& = Compare{}) {
  return {ar};
}
}
#endif  // __SOLID_ORDERED_MAP_HPP
