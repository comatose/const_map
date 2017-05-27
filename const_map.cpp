#include <utility>

using namespace std;

template<typename>
struct show_type;

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

int main() {
    show_type<value_sequence<int, 0, 1>::concat_t<value_sequence<int, 10, 20>>> x;
    show_type<concat_t<index_sequence<0, 1>, index_sequence<10, 20>>> y;
    return 0;
}
