#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid unordered_map", "[unordered_map]") {
  constexpr solid::pair<int, int> a[] = {{4, 2}, {1, 10}};
  constexpr auto z = solid::make_unordered_map(a);
  // constexpr solid::unordered_map<int, int, 2> z = {{4, 2}, {1, 10}};
  static_assert(
      std::is_same<decltype(z)::value_type, solid::pair<int, int>>::value);
  // constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
  static_assert(z[4] == 2);
  static_assert(z[1] == 10);
  static_assert(z.find(4) != z.end());
  static_assert(z.find(4)->first == 4);
  static_assert(z.find(4)->second == 2);
  static_assert(z.find(1) != z.end());
  static_assert(z.find(1)->first == 1);
  static_assert(z.find(1)->second == 10);
  static_assert(z.find(100) == z.end());

  SECTION("test find in runtime") {
    for (const auto& p : z) {
      auto it = z.find(p.first);
      REQUIRE(it != z.end());
      REQUIRE(it->first == p.first);
      REQUIRE(it->second == p.second);
      REQUIRE(z[p.first] == p.second);
    }
  }
}
