#ifndef __SOLID_UNORDERED_SET_HPP
#define __SOLID_UNORDERED_SET_HPP

#include "algorithm.hpp"
#include "array.hpp"
#include "indexer.hpp"

#include <bitset>
#include <initializer_list>

#include <cstddef>

namespace solid {

template <typename T, std::size_t N, class Indexer = simple_indexer<T, N>>
class unordered_set {
 public:
  using const_iterator = const T*;
  using value_type = T;

  constexpr unordered_set(std::initializer_list<T> init)
      : unordered_set{std::begin(init), std::end(init)} {}

  template <class Ts>
  constexpr unordered_set(const Ts& ts)
      : unordered_set{std::begin(ts), std::end(ts)} {}

  template <class InputIt>
  constexpr unordered_set(InputIt first, InputIt last) : indexer_(first, last) {
    for (; first < last; ++first) {
      auto i = indexer_.index_of(*first);
      elements_[i] = *first;
    }
  }

  constexpr std::size_t size() const { return N; }

  constexpr bool contains(const T& k) const {
    return elements_[indexer_.index_of(k)] == k;
  }

  constexpr const_iterator begin() const { return elements_.begin(); }

  constexpr const_iterator end() const { return elements_.end(); }

  constexpr const_iterator cbegin() const { return elements_.cbegin(); }

  constexpr const_iterator cend() const { return elements_.cend(); }

 private:
  Indexer indexer_;
  array<T, N> elements_{};
};

template <typename T, size_t N>
constexpr ordered_set<T, N> make_unordered_set(const T (&ar)[N]) {
  return {ar};
}
}

namespace std {

template <class T, size_t N, class Indexer>
struct tuple_size<solid::unordered_set<T, N, Indexer>>
    : integral_constant<size_t, N> {};
}

#endif  // __SOLID_UNORDERED_SET_HPP
