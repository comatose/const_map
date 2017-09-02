#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid ordered_set", "[ordered_set]") {
  constexpr int a[] = {3, 1, 10, 4, 8};
  constexpr auto b = solid::make_ordered_set(a);
  // constexpr solid::ordered_set<int, 5> b = {3, 1, 10, 4, 8};
  static_assert(b.size() == 5);
  static_assert(b.contains(3));
  static_assert(b.contains(1));
  static_assert(b.contains(10));
  static_assert(b.contains(4));
  static_assert(b.contains(8));
  static_assert(!b.contains(30));
  static_assert(!b.contains(40));
  static_assert(!b.contains(100));

  SECTION("all elements are ordered in the ordered_set") {
    auto bit = b.begin();
    REQUIRE(bit[0] == 1);
    REQUIRE(bit[1] == 3);
    REQUIRE(bit[2] == 4);
    REQUIRE(bit[3] == 8);
    REQUIRE(bit[4] == 10);
  }

  SECTION("test contains in runtime") {
    for (const auto& i : b) REQUIRE(b.contains(i));
  }
}
