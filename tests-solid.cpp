#include "catch.hpp"

#include "solid.hpp"

using namespace std;

template<typename>
struct show_type;

TEST_CASE("solid array", "[array]") {
  constexpr solid::array<int, 5> a = {3, 1, 10, 4, 8};
  constexpr auto g = quick_sort(a);
  static_assert(g[0] == 1 && g[1] == 3 && g[2] == 4 && g[3] == 8 && g[4] == 10);

  constexpr solid::array<int, 5> b(a.begin(), a.end());
  constexpr solid::array<solid::pair<int, int>, 2> c = {{1, 2}, {3, 10}};
}

TEST_CASE("solid ordered_set", "[ordered_set]") {
  constexpr solid::ordered_set<int, 5> b = {3, 1, 10, 4, 8};
  static_assert(b.end() - b.begin() == 5);
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
    for(const auto& i : b)
      REQUIRE(b.contains(i));
  }
}

TEST_CASE("solid ordered_map", "[ordered_map]") {
  constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
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
    REQUIRE(zit[1].first == 3);
  }

  SECTION("test find in runtime") {
    for(const auto& p : z)
      REQUIRE(z.find(p.first) != z.end());
  }
}

TEST_CASE("solid unordered_set", "[unordered_set]") {
  constexpr solid::unordered_set<int, 5> d = {0, 1, 2, 3, 4};
  static_assert(d.end() - d.begin() == 5);
  static_assert(d.contains(0));
  static_assert(d.contains(1));
  static_assert(d.contains(2));
  static_assert(d.contains(3));
  static_assert(d.contains(4));
  static_assert(!d.contains(5));
  static_assert(!d.contains(6));

  SECTION("test contains in runtime") {
    for(const auto& i : d)
      REQUIRE(d.contains(i));
  }
}
