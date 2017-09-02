#include "catch.hpp"

#include "solid.hpp"

TEST_CASE("solid bitset", "[bitset]") {
  solid::bitset<100> bs;
  REQUIRE(bs.count() == 0);
  bs.set(77);
  REQUIRE(bs.count() == 1);
  REQUIRE(bs.test(77));
  bs.set(77);
  REQUIRE(bs.count() == 1);
  REQUIRE(bs.test(77));
  bs.reset(77);
  REQUIRE(bs.count() == 0);
  REQUIRE(!bs.test(77));
}
