#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid hash_indexer", "[hash_indexer]") {
  constexpr int numbers[] = {1, 2, 15, 5, 7};

  SECTION("hash_indexer for numbers") {
    // selected the size greater than the actual number of elements
    // to decrease compilation time and collision probability.
    constexpr solid::hash_indexer<int, 7> indexer(numbers);

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : numbers) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  SECTION("another hash_indexer for numbers") {
    constexpr auto indexer = solid::make_hash_indexer<7>({1, 2, 15, 5, 7});

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : numbers) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  constexpr solid::static_string_view strings[] = {"hash", "indexer", "for",
                                                   "strings"};

  SECTION("hash_indexer for strings") {
    // same as the case for numbers,
    // the size is greater than the number of strings.
    constexpr solid::hash_indexer<solid::static_string_view, 5> indexer(
        strings);

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : strings) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }

  SECTION("hash_indexer for strings") {
    constexpr auto indexer =
        solid::make_hash_indexer<5, solid::static_string_view>(
            {"hash", "indexer", "for", "strings"});

    solid::array<bool, indexer.max_size()> appeared{};
    for (const auto& e : strings) {
      auto i = indexer.index_of(e);
      REQUIRE(i < indexer.max_size());
      REQUIRE(!appeared[i]);
      appeared[i] = true;
    }
  }
}
