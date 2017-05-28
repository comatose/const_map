#ifndef __CONST_MAP_HPP
#define __CONST_MAP_HPP

#include <boost/hana.hpp>

#include <cstddef>
#include <iterator>
#include <array>
#include <type_traits>
#include <utility>
#include <algorithm>

template<typename... Ts>
class const_sorted_map : public boost::hana::tuple<Ts...> {
  using base_type = boost::hana::tuple<Ts...>;
  using value_type = typename std::decay_t<decltype(std::declval<base_type>()[boost::hana::int_c<0>])>::value_type;

 public:
  constexpr const_sorted_map(base_type t)
  : const_sorted_map(t, std::index_sequence_for<Ts...>{}) {
  }

  auto index_of(const value_type& v) const {
    return std::distance(array_.begin(), std::lower_bound(array_.begin(), array_.end(), v));
  }

 private:
  const std::array<value_type, sizeof...(Ts)> array_;

  template<std::size_t... I>
  constexpr const_sorted_map(base_type t, std::index_sequence<I...>)
  : base_type(t), array_{t[boost::hana::int_c<I>]...} {
    static_assert(t == boost::hana::sort(t));
  }
};

namespace internal {
template<typename... Ts>
constexpr auto make_const_sorted_map_impl(boost::hana::tuple<Ts...> t) {
  return const_sorted_map<Ts...>(t);
}
}

template<typename... Ts>
constexpr auto make_const_sorted_map(Ts... args) {
  return internal::make_const_sorted_map_impl(boost::hana::sort(boost::hana::make_tuple(args...)));
}

#endif // __CONST_MAP_HPP
