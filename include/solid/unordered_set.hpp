#ifndef __SOLID_UNORDERED_SET_HPP
#define __SOLID_UNORDERED_SET_HPP

#include "algorithm.hpp"
#include "array.hpp"

#include <bitset>
#include <initializer_list>

#include <cstddef>

namespace solid {

namespace internal {

template<typename T, class Hash = solid::hash<T>>
constexpr std::size_t hash_with(std::size_t d, const T& value) {
  return ((d * 0x01000193) ^ Hash{}(value)) & 0xffffffff;
}

static_assert(hash_with(0, 1) == 1);

template<class Ts, std::size_t N, class Hash = solid::hash<typename Ts::value_type>>
constexpr bool unique_with(const Ts& ts, std::size_t d) {
  bool used[N]{false};
  for(const auto& e : ts) {
    auto hv = hash_with<typename Ts::value_type, Hash>(d, e) % N;
    if(used[hv]) {
      return false;
    }
    used[hv] = true;
  }
  return true;
}

template<std::size_t N, class Ts, class Hash = solid::hash<typename Ts::value_type>>
constexpr std::size_t find_min(const Ts& ts, std::size_t maxd = std::numeric_limits<std::size_t>::max()) {
  for(std::size_t d = 0; d < maxd; ++d) {
    if(unique_with<Ts, N, Hash>(ts, d))
      return d;
  }
  return maxd;
}

}

template<class T, std::size_t N, class Hash = solid::hash<T>>
struct simple_indexer {

  template<class Ts>
  constexpr simple_indexer(const Ts& ts)
  : d(internal::find_min<N, Ts, Hash>(ts)) {
    static_assert(std::is_same<typename Ts::value_type, T>::value);
  }

  constexpr std::size_t index_of(std::size_t i) const {
    return internal::hash_with<T, Hash>(d, i) % N;
  }

 private:
  std::size_t d{};
};

template<typename T, std::size_t N, class Indexer = simple_indexer<T, N>>
class unordered_set {
 public:
  using iterator = T*;
  using const_iterator = const T*;
  using value_type = T;

  constexpr unordered_set() = default;

  constexpr unordered_set(std::initializer_list<T> init)
  : indexer_{init} {
    for(const auto& k : init) {
      auto i = indexer_.index_of(k);
      container_[i] = k;
    }
  }

  constexpr bool contains(const T& k) const {
    return container_[indexer_.index_of(k)] == k;
  }

 private:
  Indexer indexer_{};
  array<T, N> container_{};
};

}

namespace std {

template<class T, size_t N, class Indexer>
struct tuple_size<solid::unordered_set<T, N, Indexer>> : integral_constant<size_t, N>
{};

}

#endif // __SOLID_UNORDERED_SET_HPP
