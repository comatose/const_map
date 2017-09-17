#ifndef __SOLID_TABLE_INDEXER_HPP
#define __SOLID_TABLE_INDEXER_HPP

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
struct table_indexer {
  constexpr table_indexer(std::initializer_list<T> init)
      : table_indexer{init.begin(), init.end()} {}

  template <class Ts>
  constexpr table_indexer(const Ts& ts)
      : table_indexer{std::begin(ts), std::end(ts)} {}

  template <class InputIt>
  constexpr table_indexer(InputIt first, InputIt last) {
    static_assert(
        std::is_same<
            std::decay_t<typename std::iterator_traits<InputIt>::value_type>,
            T>::value);
    assert(first <= last);
    assert(last - first <= N);

    array<stack<T, N>, N> groups;
    for (; first < last; ++first)
      groups[internal::hash_with<T, Hash>(0, *first) % N].push(*first);

    // use bubble_sort to avoid too deep recursion.
    bubble_sort(groups.begin(), groups.end(), size_reverse_comparer{});
    constexpr auto maxd = std::numeric_limits<int>::max();
    array<bool, N> used{};
    for (const stack<T, N>& group : groups) {
      if (group.size() == 0) break;

      if (group.size() == 1) {
        for (auto i = 0U; i < N; ++i) {
          if (!used[i]) {
            table_[internal::hash_with<T, Hash>(0, group.top()) % N] = -i;
            used[i] = true;
            break;
          }
        }
        continue;
      }

      int d = find_min(group, used, 1, maxd);
      assert(d != maxd);

      table_[internal::hash_with<T, Hash>(0, group.top()) % N] = d;
    }
  }

  constexpr std::size_t index_of(const T& e) const {
    auto d = internal::hash_with<T, Hash>(0, e) % N;
    if (table_[d] <= 0) return -table_[d];

    return internal::hash_with<T, Hash>(table_[d], e) % N;
  }

  constexpr std::size_t max_size() const { return N; }

 private:
  int table_[N]{};

  struct size_reverse_comparer {
    template <class U>
    constexpr bool operator()(const U& lhs, const U& rhs) {
      return rhs.size() < lhs.size();
    }
  };

  template <class Ts>
  constexpr std::size_t find_min(
      const Ts& ts, array<bool, N>& used, std::size_t mind = 0,
      std::size_t maxd = std::numeric_limits<std::size_t>::max()) {
    for (std::size_t d = mind; d < maxd; ++d) {
      auto used2 = used;
      if (unique_with(ts, d, used2)) {
        used = used2;
        return d;
      }
    }
    return maxd;
  }

  template <class Ts>
  constexpr bool unique_with(const Ts& ts, std::size_t d,
                             array<bool, N>& used) {
    for (const auto& e : ts) {
      auto hv = internal::hash_with<typename Ts::value_type, Hash>(d, e) % N;
      if (used[hv]) {
        return false;
      }
      used[hv] = true;
    }
    return true;
  }
};

template <typename T, size_t N>
constexpr table_indexer<T, N> make_table_indexer(const T (&ar)[N]) {
  return {&ar[0], &ar[N]};
}

template <size_t M, typename T, size_t N>
constexpr table_indexer<T, M> make_table_indexer(const T (&ar)[N]) {
  return {&ar[0], &ar[N]};
}
}

#endif  // __SOLID_TABLE_INDEXER_HPP
