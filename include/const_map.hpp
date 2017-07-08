#ifndef __CONST_MAP_HPP
#define __CONST_MAP_HPP

#include <boost/hana.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>

template <typename T, T... Is>
class const_sorted_map {
 public:
  using value_type = T;

  constexpr const_sorted_map()
      : array_(boost::hana::unpack(ordered_tuple, [](auto... args) {
          return decltype(array_){args...};
        })) {}

  constexpr std::size_t index_of(const value_type& v) const {
    return std::distance(array_.begin(),
                         std::lower_bound(array_.begin(), array_.end(), v));
  }

  template <value_type N>
  constexpr std::size_t index_of(
      boost::hana::integral_constant<value_type, N> i) const {
    return boost::hana::length(
        boost::hana::take_while(ordered_tuple, boost::hana::not_equal.to(i)));
  }

  constexpr std::size_t size() const { return sizeof...(Is); }

 private:
  static constexpr auto ordered_tuple =
      boost::hana::sort(boost::hana::tuple_c<value_type, Is...>);

  const std::array<value_type, sizeof...(Is)> array_;
};

#endif  // __CONST_MAP_HPP
