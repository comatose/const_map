#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid ordered_map", "[ordered_map]") {
  constexpr solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
  constexpr auto z = solid::make_ordered_map(a);
  // constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
  static_assert(z[3] == 2);
  static_assert(z[1] == 10);
  static_assert(z.find(3) != z.end());
  static_assert(z.find(3)->first == 3);
  static_assert(z.find(3)->second == 2);
  static_assert(z.find(1) != z.end());
  static_assert(z.find(1)->first == 1);
  static_assert(z.find(1)->second == 10);
  static_assert(z.find(100) == z.end());

  SECTION("all elements are ordered in the ordered_map") {
    auto zit = z.begin();
    REQUIRE(zit[0].first == 1);
    REQUIRE(zit[0].second == 10);
    REQUIRE(zit[1].first == 3);
    REQUIRE(zit[1].second == 2);
  }

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
