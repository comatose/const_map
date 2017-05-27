#ifndef __VALUE_SEQUENCE_HPP
#define __VALUE_SEQUENCE_HPP

#include <utility>

template<typename T, T...>
struct value_sequence {
};

template<typename T, T head, T... tail>
struct value_sequence<T, head, tail...> {
  static constexpr auto head_value = head;

  template<typename>
  struct concat {
  };

  template<T... rhs>
  struct concat<value_sequence<T, rhs...>> {
    using type = value_sequence<T, head, tail..., rhs...>;
  };

  template<typename U>
  using concat_t = typename concat<U>::type;
};

template<typename, typename>
struct concat {
};

template<template<typename _, _...> class C, typename T, T... T0, T... T1>
struct concat<C<T, T0...>, C<T, T1...>> {
  using type = C<T, T0..., T1...>;
};

template<typename T, typename U>
using concat_t = typename concat<T, U>::type;

#endif // __VALUE_SEQUENCE_HPP
