#ifndef __SOLID_UNORDERED_SET_HPP
#define __SOLID_UNORDERED_SET_HPP

#include <cstddef>

#include <initializer_list>

#include "algorithm.hpp"
#include "array.hpp"
#include "bitset.hpp"
#include "hash_indexer.hpp"

namespace solid {

template <typename T, std::size_t N, class Indexer = hash_indexer<T, N>>
class unordered_set {
 public:
  struct const_iterator {
    constexpr const const_iterator& operator++() {
      advance();
      return *this;
    }

    constexpr const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++(*this);
      return tmp;
    }

    constexpr bool operator!=(const const_iterator& other) const {
      return &other.set_ != &set_ || other.position_ != position_;
    }

    constexpr bool operator==(const const_iterator& other) const {
      return &other.set_ == &set_ && other.position_ == position_;
    }

    const T& operator*() const { return set_.elements_[position_]; }

   private:
    constexpr const_iterator(const unordered_set& set) : set_(set) {
      if (!set_.occupied_.test(0)) advance();
    }

    constexpr const_iterator(const unordered_set& set, std::size_t pos)
        : set_(set), position_(pos) {}

    constexpr const_iterator(const const_iterator& other)
        : const_iterator(other.set_, other.position_) {}

    void advance() {
      ++position_;
      for (; position_ < set_.capacity() && !set_.occupied_.test(position_);
           ++position_) {
      }
    }

    const unordered_set& set_;
    std::size_t position_{0};
  };

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
      occupied_.set(i);
    }
  }

  constexpr std::size_t size() const { return occupied_.count(); }

  constexpr std::size_t capacity() const { return N; }

  constexpr bool contains(const T& k) const {
    auto i = indexer_.index_of(k);
    return occupied_.test(i) && elements_[i] == k;
  }

  constexpr const_iterator begin() const { return {*this}; }

  constexpr const_iterator end() const { return {*this, N}; }

  constexpr const_iterator cbegin() const { return {*this}; }

  constexpr const_iterator cend() const { return {*this, N}; }

 private:
  Indexer indexer_;
  array<T, N> elements_{};
  bitset<N> occupied_{};
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
