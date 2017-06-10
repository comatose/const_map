#ifndef __SOLID_ALGORITHM_HPP
#define __SOLID_ALGORITHM_HPP

#include <algorithm>
#include <cstddef>

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

template<typename T, typename = std::enable_if_t<std::is_integral<T>::value>>
constexpr std::size_t hash(const T& value) {
  return value;
}

template<typename T>
constexpr std::size_t hash(std::size_t d, const T& value) {
  return ((d * 0x01000193) ^ hash(value)) & 0xffffffff;
}

}
#endif // __SOLID_ALGORITHM_HPP
