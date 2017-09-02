#include <type_traits>

#include "catch.hpp"

#include "solid.hpp"

TEST_CASE("solid lens", "[lens]") {
  SECTION("use value") {
    constexpr solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
    constexpr auto get_first = [](const auto& p) { return p.first; };

    static_assert(
        std::is_same<decltype(make_lens(&a[0], get_first))::value_type,
                     int>::value);
    static_assert(*make_lens(&a[0], get_first) == 3);
    static_assert(*make_lens(&a[1], get_first) == 1);
  }

  SECTION("use reference") {
    solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
    auto get_first = [](auto& p) -> decltype(p.first)& { return p.first; };

    auto it = make_lens(std::begin(a), get_first);
    static_assert(std::is_same<decltype(it)::value_type, int&>::value);
    for (; it != make_lens(std::end(a), get_first); ++it) {
      (*it)++;
    }

    REQUIRE(a[0].first == 4);
    REQUIRE(a[0].second == 2);
    REQUIRE(a[1].first == 2);
    REQUIRE(a[1].second == 10);
  }
}
