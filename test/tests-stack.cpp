#include "catch.hpp"

#include "solid.hpp"

TEST_CASE("solid stack", "[stack]") {
  constexpr solid::stack<int, 10> a = {3, 1, 10, 4, 8};
  static_assert(a.size() == 5);
  static_assert(a.capacity() == 10);
  static_assert(std::tuple_size<decltype(a)>::value == 10);

  solid::stack<int, 10> b(a.begin(), a.end());
  REQUIRE(b.size() == 5);
  b.push(9);
  REQUIRE(b.size() == 6);
  REQUIRE(b.pop() == 9);
  REQUIRE(b.size() == 5);
}
