#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid table_indexer", "[table_indexer]") {
  constexpr int a[] = {1, 2, 15, 5, 7, 6};
  constexpr size_t N = 6;
  constexpr solid::table_indexer<int, N> indexer(a);

  solid::array<bool, N> b{};
  for (const auto& e : a) {
    auto i = indexer.index_of(e);
    REQUIRE(i < N);
    REQUIRE(!b[i]);
    b[i] = true;
  }
}
