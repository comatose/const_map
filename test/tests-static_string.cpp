#include "catch.hpp"

#include "solid.hpp"
#include "solid/static_string.hpp"

TEST_CASE("solid static_string", "[string]") {
  constexpr const char* str = "hi";
  constexpr solid::static_string<2> a(str);
  static_assert(a[0] == 'h' && a[1] == 'i');

  constexpr solid::static_string<2> a1("hi");
  static_assert(a1[0] == 'h' && a1[1] == 'i');

  constexpr solid::static_string_view a2("hi");
  static_assert(a2[0] == 'h' && a2[1] == 'i');

  constexpr auto a3 = a2;
  static_assert(a3[0] == 'h' && a3[1] == 'i');

  auto a4 = a3;
  REQUIRE(a4[0] == 'h');
  REQUIRE(a4[1] == 'i');
}
