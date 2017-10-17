#ifndef __SOLID_UNORDERED_MAP_HPP
#define __SOLID_UNORDERED_MAP_HPP

#include <cstddef>

#include <initializer_list>

#include "algorithm.hpp"
#include "array.hpp"
#include "bitset.hpp"
#include "hash_indexer.hpp"
#include "lens.hpp"

namespace solid {

template <typename Key, typename Value, std::size_t N,
          class Indexer = hash_indexer<Key, N>>
class unordered_map {
 public:
  using value_type = pair<Key, Value>;

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
      return &other.owner_ != &owner_ || other.position_ != position_;
    }

    constexpr bool operator==(const const_iterator& other) const {
      return &other.owner_ == &owner_ && other.position_ == position_;
    }

    constexpr const value_type& operator*() const {
      return owner_.elements_[position_];
    }

    constexpr const value_type* operator->() const {
      return &owner_.elements_[position_];
    }

   private:
    constexpr const_iterator(const unordered_map& set) : owner_(set) {
      if (!owner_.occupied_.test(0)) advance();
    }

    constexpr const_iterator(const unordered_map& set, std::size_t pos)
        : owner_(set), position_(pos) {}

    constexpr const_iterator(const const_iterator& other)
        : const_iterator(other.owner_, other.position_) {}

    void advance() {
      ++position_;
      for (; position_ < owner_.capacity() && !owner_.occupied_.test(position_);
           ++position_) {
      }
    }

    const unordered_map& owner_;
    std::size_t position_{0};
  };

  constexpr unordered_map(std::initializer_list<value_type> init)
      : unordered_map{std::begin(init), std::end(init)} {}

  template <class Ts>
  constexpr unordered_map(const Ts& ts)
      : unordered_map{std::begin(ts), std::end(ts)} {}

  template <class InputIt>
  constexpr unordered_map(InputIt begin, InputIt end)
      : indexer_(make_lens(begin, get_first), make_lens(end, get_first)) {
    for (; begin < end; ++begin) {
      auto i = indexer_.index_of(begin->first);
      elements_[i] = *begin;
      occupied_.set(i);
    }
  }

  constexpr const Value& operator[](const Key& key) const {
    auto it = find(key);
    assert(it != cend());

    return it->second;
  }

  constexpr const_iterator find(const Key& k) const {
    auto i = indexer_.index_of(k);
    if (!occupied_.test(i) || elements_[i].first != k) return end();
    return {*this, i};
  }

  constexpr std::size_t size() const { return occupied_.count(); }

  constexpr std::size_t capacity() const { return N; }

  constexpr const_iterator begin() const { return {*this}; }

  constexpr const_iterator end() const { return {*this, N}; }

  constexpr const_iterator cbegin() const { return {*this}; }

  constexpr const_iterator cend() const { return {*this, N}; }

 private:
  static constexpr const Key& get_first(const value_type& v) { return v.first; }

  Indexer indexer_;
  array<value_type, N> elements_{};
  bitset<N> occupied_{};
};

template <typename Key, typename Value, size_t N>
constexpr unordered_map<Key, Value, N> make_unordered_map(
    const pair<Key, Value> (&ar)[N]) {
  return {ar};
}

template <size_t M, typename Key, typename Value, size_t N>
constexpr unordered_map<Key, Value, M> make_unordered_map(
    const pair<Key, Value> (&ar)[N]) {
  return {ar};
}
}  // namespace solid

namespace std {

template <class Key, typename Value, size_t N, class Indexer>
struct tuple_size<solid::unordered_map<Key, Value, N, Indexer>>
    : integral_constant<size_t, N> {};
}  // namespace std

#endif  // __SOLID_UNORDERED_MAP_HPP
