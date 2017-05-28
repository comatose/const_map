#ifndef __SOLID_HPP
#define __SOLID_HPP

#include <array>
#include <utility>
#include <iostream>
#include <algorithm>

namespace solid {

template<class T>
constexpr void swap(T& a, T& b) {
  T tmp = std::move(b);
  b = std::move(a);
  a = std::move(tmp);
}

template<class InputIt, class OutputIt>
constexpr OutputIt copy(InputIt first, InputIt last, OutputIt dst) {
  while(first != last)
    *(dst++) = *(first++);
  return dst;
}

template<class RandomIt>
constexpr RandomIt partition(RandomIt first, RandomIt last){
  --last;
  RandomIt it = first;
  for(; it != last; ++it){
    if(*it < *last){
      swap(*it, *first);
      first++;
    }
  }
  swap(*first, *last);
  return first;
}

template<class RandomIt>
constexpr void quick_sort(RandomIt first, RandomIt last){
  if(first >= last) return;

  RandomIt pivot = partition(first, last);
  quick_sort(first, pivot);
  quick_sort(pivot + 1, last);
}

template<class T>
constexpr T quick_sort(T a) {
  quick_sort(a.begin(), a.end());
  return a;
}

template<class RandomIt, class V>
constexpr RandomIt binary_search(RandomIt first, RandomIt last, const V& value){
  RandomIt notfound = last;
  while(first < last){
    RandomIt mid = first + (last - first) / 2;
    if(*mid == value)
      return mid;
    else if(*mid < value)
      first = mid + 1;
    else
      last = mid;
  }
  return notfound;
}

template<typename T, std::size_t N>
class array {
 public:
  using iterator = T*;
  using const_iterator = const T*;

  constexpr array() = default;

  constexpr array(const array& other)
  : array(other.cbegin(), other.cend()) {
  }

  template<class InputIt>
  constexpr array(InputIt first, InputIt last) {
    copy(first, last, begin());
  }

  constexpr array(std::initializer_list<T> init) {
    copy(init.begin(), init.end(), begin());
  }

  constexpr std::size_t size() const {
    return N;
  }

  constexpr T& operator[](std::size_t i) {
    return elements_[i];
  }

  constexpr const T& operator[](std::size_t i) const {
    return elements_[i];
  }

  constexpr iterator begin() {
    return &elements_[0];
  }

  constexpr iterator end() {
    return &elements_[N];
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
  T elements_[N]{};
};

template<typename Key, std::size_t N>
class ordered_set : public array<Key, N> {
  using base_type = array<Key, N>;
 public:
  using iterator = Key*;
  using const_iterator = const Key*;

  using base_type::begin;
  using base_type::end;
  using base_type::cbegin;
  using base_type::cend;
  using base_type::size;
  using base_type::operator[];

  constexpr ordered_set() = default;

  constexpr ordered_set(const ordered_set& other)
  : base_type(other) {
  }

  template<class InputIt>
  constexpr ordered_set(InputIt first, InputIt last)
  : base_type(first, last) {
    quick_sort(begin(), end());
  }

  constexpr ordered_set(std::initializer_list<Key> init)
  : base_type(init) {
    quick_sort(begin(), end());
  }

  constexpr iterator find(const Key& k) {
    return binary_search(begin(), end(), k);
  }

  constexpr const_iterator find(const Key& k) const {
    return binary_search(cbegin(), cend(), k);
  }
};

template<typename First, typename Second>
struct pair{
  First first;
  Second second;
};

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
    return values_[keys_.find(key) - keys_.begin()];
  }

  constexpr const Value& operator[](const Key& key) const {
    return values_[keys_.find(key) - keys_.begin()];
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
};

}
#endif // __SOLID_HPP
