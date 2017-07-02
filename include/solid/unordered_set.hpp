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

static_assert(hash_with(0, 1) == solid::hash<int>{}(1));

}

template<class T, std::size_t N, class Hash = solid::hash<T>>
struct simple_indexer {

  template<class Ts>
  constexpr simple_indexer(const Ts& ts)
  : d(find_min(ts)) {
    static_assert(std::is_same<typename Ts::value_type, T>::value);
  }

  constexpr std::size_t index_of(const T& e) const {
    return internal::hash_with<T, Hash>(d, e) % N;
  }

 private:
  std::size_t d{};

  template<class Ts>
  constexpr std::size_t find_min(const Ts& ts, std::size_t mind = 0,
                                 std::size_t maxd = std::numeric_limits<std::size_t>::max()) {
    for(std::size_t d = mind; d < maxd; ++d) {
      if(unique_with<Ts>(ts, d))
        return d;
    }
    return maxd;
  }

  template<class Ts>
  constexpr bool unique_with(const Ts& ts, std::size_t d) {
    bool used[N]{false};
    for(const auto& e : ts) {
      auto hv = internal::hash_with<typename Ts::value_type, Hash>(d, e) % N;
      if(used[hv]) {
        return false;
      }
      used[hv] = true;
    }
    return true;
  }
};

template<class T, std::size_t N, class Hash = solid::hash<T>>
struct table_indexer {
  template<class Ts>
  constexpr table_indexer(const Ts& ts) {
    static_assert(std::is_same<typename Ts::value_type, T>::value);

    array<stack<T, N>, N> groups;
    for(const auto& e : ts)
      groups[internal::hash_with<T, Hash>(0, e) % N].push(e);

    quick_sort(groups.begin(), groups.end(), size_reverse_comparer{});
    constexpr auto maxd = std::numeric_limits<int>::max();
    array<bool, N> used{};
    for(const stack<T, N>& group : groups) {
      if(group.size() == 0)
        break;

      if(group.size() == 1) {
        for(auto i = 0U; i < N; ++i) {
          if(!used[i]) {
            table_[internal::hash_with<T, Hash>(0, group.top()) % N] = -i;
            used[i] = true;
            break;
          }
        }
        continue;
      }

      int d = find_min(group, used, 1, maxd);
      if(d == maxd) // TODO: handle this case
        break;

      table_[internal::hash_with<T, Hash>(0, group.top()) % N] = d;
    }

  }

  constexpr std::size_t index_of(const T& e) const {
    auto d = internal::hash_with<T, Hash>(0, e) % N;
    if(table_[d] <= 0)
      return -table_[d];

    return internal::hash_with<T, Hash>(table_[d], e) % N;
  }

 private:
  int table_[N]{};

  struct size_reverse_comparer {
    template<class U>
    constexpr bool operator()(const U& lhs, const U& rhs) {
      return rhs.size() < lhs.size();
    }
  };

  template<class Ts>
  constexpr std::size_t find_min(const Ts& ts, array<bool, N>& used, std::size_t mind = 0, std::size_t maxd = std::numeric_limits<std::size_t>::max()) {
    for(std::size_t d = mind; d < maxd; ++d) {
      auto used2 = used;
      if(unique_with(ts, d, used2)) {
        used = used2;
        return d;
      }
    }
    return maxd;
  }

  template<class Ts>
  constexpr bool unique_with(const Ts& ts, std::size_t d, array<bool, N>& used) {
    for(const auto& e : ts) {
      auto hv = internal::hash_with<typename Ts::value_type, Hash>(d, e) % N;
      if(used[hv]) {
        return false;
      }
      used[hv] = true;
    }
    return true;
  }
};

template<typename T, std::size_t N, class Indexer = simple_indexer<T, N>>
class unordered_set {
 public:
  using const_iterator = const T*;
  using value_type = T;

  constexpr unordered_set() = default;

  constexpr unordered_set(std::initializer_list<T> init)
  : indexer_{init} {
    for(const auto& k : init) {
      auto i = indexer_.index_of(k);
      elements_[i] = k;
    }
  }

  constexpr bool contains(const T& k) const {
    return elements_[indexer_.index_of(k)] == k;
  }

  constexpr const_iterator begin() const {
    return &elements_[0];
  }

  constexpr const_iterator end() const {
    return &elements_[N];
  }

  constexpr const_iterator cbegin() const {
    return &elements_[0];
  }

  constexpr const_iterator cend() const {
    return &elements_[N];
  }

 private:
  Indexer indexer_{};
  array<T, N> elements_{};
};

}

namespace std {

template<class T, size_t N, class Indexer>
struct tuple_size<solid::unordered_set<T, N, Indexer>> : integral_constant<size_t, N>
{};

}

#endif // __SOLID_UNORDERED_SET_HPP
