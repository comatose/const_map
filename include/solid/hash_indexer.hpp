#ifndef __SOLID_INDEXER_HPP
#define __SOLID_INDEXER_HPP

#include <cassert>
#include <cstddef>

#include <initializer_list>
#include <iterator>
#include <type_traits>

#include "array.hpp"
#include "hash.hpp"
#include "stack.hpp"

namespace solid {

template <class T, std::size_t N, class Hash = solid::hash<T>>
struct hash_indexer {
  constexpr hash_indexer(std::initializer_list<T> init)
      : hash_indexer{init.begin(), init.end()} {}

  template <class Ts>
  constexpr hash_indexer(const Ts& ts)
      : hash_indexer(std::begin(ts), std::end(ts)) {}

  template <class InputIt>
  constexpr hash_indexer(InputIt first, InputIt last) {
    static_assert(
        std::is_same<
            std::decay_t<typename std::iterator_traits<InputIt>::value_type>,
            T>::value);
    assert(first <= last);
    assert(last - first <= N);

    for (d = 0; d < std::numeric_limits<std::size_t>::max(); ++d) {
      if (unique_with(first, last, d)) break;
    }
    assert(d != std::numeric_limits<std::size_t>::max());
  }

  constexpr std::size_t index_of(const T& e) const {
    return internal::hash_with<T, Hash>(d, e) % N;
  }

  constexpr std::size_t max_size() const { return N; }

 private:
  std::size_t d{};

  template <class InputIt>
  constexpr bool unique_with(InputIt first, InputIt last, std::size_t d) {
    bool used[N]{false};
    for (; first < last; ++first) {
      auto hv = internal::hash_with<T, Hash>(d, *first) % N;
      if (used[hv]) {
        return false;
      }
      used[hv] = true;
    }
    return true;
  }
};

template <typename T, size_t N>
constexpr hash_indexer<T, N> make_hash_indexer(const T (&ar)[N]) {
  return {&ar[0], &ar[N]};
}

template <size_t M, typename T, size_t N>
constexpr hash_indexer<T, M> make_hash_indexer(const T (&ar)[N]) {
  return {&ar[0], &ar[N]};
}
}

#endif  // __SOLID_INDEXER_HPP
