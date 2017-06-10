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
 public:
  using iterator = Key*;
  using const_iterator = const Key*;

  constexpr ordered_map() = default;

  constexpr ordered_map(std::initializer_list<pair<Key, Value>> init)
  : keys_(create_keys(init)) {
    for(const auto & entry : init)
      values_[keys_.find(entry.first) - keys_.begin()] = entry.second;
  }

  constexpr Value& operator[](const Key& key) {
    return values_[index_of(key)];
  }

  constexpr const Value& operator[](const Key& key) const {
    return values_[index_of(key)];
  }

 private:
  ordered_set<Key, N> keys_;
  array<Value, N> values_;

  static constexpr ordered_set<Key, N> create_keys(std::initializer_list<pair<Key, Value>> init) {
    array<Key, N> ks;
    auto kit = ks.begin();
    for(const auto & entry : init)
      *(kit++) = entry.first;

    return ordered_set<Key, N>{ks.begin(), ks.end()};
  }

  constexpr std::size_t index_of(const Key& key) const {
    return keys_.find(key) - keys_.begin();
  }
};

}
#endif // __SOLID_ORDERED_MAP_HPP
