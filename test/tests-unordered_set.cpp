#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid unordered_set", "[unordered_set]") {
  SECTION("each is unique with seed of 0.") {
    constexpr int a[] = {0, 1, 2, 3, 4};
    constexpr auto d = solid::make_unordered_set(a);
    static_assert(d.size() == 5);
    static_assert(d.contains(0));
    static_assert(d.contains(1));
    static_assert(d.contains(2));
    static_assert(d.contains(3));
    static_assert(d.contains(4));
    static_assert(!d.contains(5));
    static_assert(!d.contains(6));

    SECTION("test contains in runtime") {
      for (const auto& i : {0, 1, 2, 3, 4}) {
        REQUIRE(d.contains(i));
      }
    }
  }

  SECTION("some redundancy can prevent failure in building unordered_set") {
    constexpr solid::unordered_set<int, 11> d = {1, 15, 5, 7, 6, 22, 11};
    for (const auto& e : d) {
      REQUIRE(d.contains(e));
    }
  }

  SECTION("some redundancy can prevent failure in building unordered_set") {
    constexpr auto d = solid::make_unordered_set<11>({1, 15, 5, 7, 6, 22, 11});
    for (const auto& e : d) {
      REQUIRE(d.contains(e));
    }
  }
}

TEST_CASE("solid unordered_set with table_indexer", "[unordered_set]") {
  SECTION("each is unique with seed of 0.") {
    constexpr solid::unordered_set<int, 5, solid::table_indexer<int, 5>> d = {
        0, 1, 2, 3, 4};
    static_assert(d.size() == 5);
    static_assert(d.contains(0));
    static_assert(d.contains(1));
    static_assert(d.contains(2));
    static_assert(d.contains(3));
    static_assert(d.contains(4));
    static_assert(!d.contains(5));
    static_assert(!d.contains(6));

    SECTION("test contains in runtime") {
      for (const auto& i : {0, 1, 2, 3, 4}) {
        REQUIRE(d.contains(i));
      }
    }
  }

  SECTION("there are some collisions.") {
    constexpr solid::unordered_set<int, 7, solid::table_indexer<int, 7>> d = {
        0, 1, 2, 15, 5, 7, 6};
    static_assert(d.size() == 7);
    static_assert(d.contains(0));
    static_assert(d.contains(1));
    static_assert(d.contains(2));
    static_assert(d.contains(15));
    static_assert(d.contains(5));
    static_assert(d.contains(7));
    static_assert(d.contains(6));
    static_assert(!d.contains(35));
    static_assert(!d.contains(69));

    SECTION("test contains in runtime") {
      for (const auto& i : {0, 1, 2, 15, 5, 7, 6}) {
        REQUIRE(d.contains(i));
      }
    }
  }
}

TEST_CASE("solid unordered_set for strings", "[unordered_set]") {
  SECTION("each is unique with seed of 0.") {
    constexpr solid::static_string_view a[] = {"each", "is", "unique", "with",
                                               "seed"};
    constexpr auto d = solid::make_unordered_set(a);
    static_assert(d.size() == 5);
    static_assert(d.contains("each"));
    static_assert(d.contains("is"));
    static_assert(d.contains("unique"));
    static_assert(d.contains("with"));
    static_assert(d.contains("seed"));

    SECTION("test contains in runtime") {
      for (const auto& i : solid::make_array<solid::static_string_view>(
               {"each", "is", "unique", "with", "seed"})) {
        REQUIRE(d.contains(i));
      }
    }
  }

  SECTION("some redundancy can prevent failure in building unordered_set") {
    constexpr solid::unordered_set<solid::static_string_view, 5> d = {
        "each", "is", "unique", "with"};

    for (const auto& i : solid::make_array<solid::static_string_view>(
             {"each", "is", "unique", "with"})) {
      REQUIRE(d.contains(i));
    }
  }
}
