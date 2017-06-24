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
  constexpr ordered_map() = default;

  constexpr ordered_map(std::initializer_list<pair<Key, Value>> init) {
    auto kit = keys_.begin();
    for(const auto& entry : init)
      *(kit++) = entry.first;
    quick_sort(keys_.begin(), keys_.end());

    for(const auto& entry : init)
      values_[index_of(entry.first)] = entry.second;
  }

  constexpr Value& operator[](const Key& key) {
    return values_[index_of(key)];
  }

  constexpr const Value& operator[](const Key& key) const {
    return values_[index_of(key)];
  }

 private:
  array<Key, N> keys_{};
  array<Value, N> values_{};

  constexpr std::size_t index_of(const Key& k) const {
    return binary_search(keys_.begin(), keys_.end(), k) - keys_.begin();
  }
};

}
#endif // __SOLID_ORDERED_MAP_HPP
