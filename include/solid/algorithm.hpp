#ifndef __SOLID_ALGORITHM_HPP
#define __SOLID_ALGORITHM_HPP

#include <algorithm>
#include <cstddef>

namespace solid {

template <class T>
constexpr void swap(T& a, T& b) {
  T tmp = std::move(b);
  b = std::move(a);
  a = std::move(tmp);
}

template <class InputIt, class OutputIt>
constexpr OutputIt copy(InputIt first, InputIt last, OutputIt dst) {
  while (first != last) *(dst++) = *(first++);
  return dst;
}

template <class RandomIt>
constexpr RandomIt partition(RandomIt first, RandomIt last) {
  --last;
  RandomIt it = first;
  for (; it != last; ++it) {
    if (*it < *last) {
      swap(*it, *first);
      first++;
    }
  }
  swap(*first, *last);
  return first;
}

template <class RandomIt, class Compare>
constexpr RandomIt partition(RandomIt first, RandomIt last, Compare comp) {
  --last;
  RandomIt it = first;
  for (; it != last; ++it) {
    if (comp(*it, *last)) {
      swap(*it, *first);
      first++;
    }
  }
  swap(*first, *last);
  return first;
}

template <class RandomIt>
constexpr void quick_sort(RandomIt first, RandomIt last) {
  if (first >= last) return;

  RandomIt pivot = partition(first, last);
  quick_sort(first, pivot);
  quick_sort(pivot + 1, last);
}

template <class RandomIt, class Compare>
constexpr void quick_sort(RandomIt first, RandomIt last, Compare comp) {
  if (first >= last) return;

  RandomIt pivot = partition(first, last, comp);
  quick_sort(first, pivot, comp);
  quick_sort(pivot + 1, last, comp);
}

template <class T>
constexpr T quick_sort(T a) {
  quick_sort(a.begin(), a.end());
  return a;
}

template <class RandomIt>
constexpr void bubble_sort(RandomIt first, RandomIt last) {
  for (auto i = last - 1; i > first; --i) {
    for (auto j = first; j < i; ++j) {
      if (*j > *(j + 1)) swap(*j, *(j + 1));
    }
  }
}

template <class RandomIt, class Compare>
constexpr void bubble_sort(RandomIt first, RandomIt last, Compare comp) {
  for (auto i = last - 1; i > first; --i) {
    for (auto j = first; j < i; ++j) {
      if (comp(*(j + 1), *j)) swap(*j, *(j + 1));
    }
  }
}

template <class T>
constexpr T bubble_sort(T a) {
  bubble_sort(a.begin(), a.end());
  return a;
}

template <class RandomIt, class V>
constexpr RandomIt binary_search(RandomIt first, RandomIt last,
                                 const V& value) {
  RandomIt notfound = last;
  while (first < last) {
    RandomIt mid = first + (last - first) / 2;
    if (*mid == value)
      return mid;
    else if (*mid < value)
      first = mid + 1;
    else
      last = mid;
  }
  return notfound;
}

template <class RandomIt, class V, class Compare>
constexpr RandomIt binary_search(RandomIt first, RandomIt last, const V& value,
                                 Compare comp) {
  const RandomIt notfound = last;
  while (first < last) {
    RandomIt mid = first + (last - first) / 2;
    if (comp(*mid, value))
      first = mid + 1;
    else if (comp(value, *mid))
      last = mid;
    else
      return mid;
  }
  return notfound;
}

template <class InputIt, class T, class BinaryOperation>
constexpr T accumulate(InputIt first, InputIt last, T init,
                       BinaryOperation op) {
  for (; first != last; ++first) {
    init = op(init, *first);
  }
  return init;
}

template <class InputIt, class OutputIt, class UnaryOperation>
constexpr OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first,
                             UnaryOperation unary_op) {
  while (first1 != last1) {
    *d_first++ = unary_op(*first1++);
  }
  return d_first;
}

template <class InputIt, class UnaryFunction>
constexpr UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f) {
  for (; first != last; ++first) {
    f(*first);
  }
  return f;
}

template <typename T, typename = void>
struct hash {};

template <typename T>
struct hash<T, std::enable_if_t<std::is_integral<T>::value>> {
  constexpr std::size_t operator()(const T& value) { return value; }
};
}
#endif  // __SOLID_ALGORITHM_HPP
