#include "catch.hpp"

#include "solid.hpp"
#include "solid/static_string.hpp"

TEST_CASE("solid static_string", "[string]") {
  constexpr const char* str = "hi";
  constexpr solid::static_string<3> a(str);
  static_assert(a[0] == 'h' && a[1] == 'i');

  constexpr solid::static_string<3> a1("hi");
  static_assert(a1[0] == 'h' && a1[1] == 'i');

  constexpr solid::static_string_view a2("hi");
}
