#include <cstddef>

#include <iostream>
#include <type_traits>

#include "catch.hpp"

#define private public
#include "solid.hpp"

template <typename>
struct show_type;

TEST_CASE("solid array", "[array]") {
  constexpr solid::array<int, 5> a = {3, 1, 10, 4, 8};
  constexpr auto g = quick_sort(a);
  static_assert(g[0] == 1 && g[1] == 3 && g[2] == 4 && g[3] == 8 && g[4] == 10);

  constexpr solid::array<int, 5> b(a.begin(), a.end());
  constexpr solid::array<solid::pair<int, int>, 2> c = {{1, 2}, {3, 10}};
}

TEST_CASE("solid stack", "[stack]") {
  constexpr solid::stack<int, 10> a = {3, 1, 10, 4, 8};
  static_assert(a.size() == 5);
  static_assert(a.capacity() == 10);

  solid::stack<int, 10> b(a.begin(), a.end());
  REQUIRE(b.size() == 5);
  b.push(9);
  REQUIRE(b.size() == 6);
  REQUIRE(b.pop() == 9);
  REQUIRE(b.size() == 5);
}

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

TEST_CASE("solid ordered_map", "[ordered_map]") {
  constexpr solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
  constexpr auto z = solid::make_ordered_map(a);
  // constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
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
    REQUIRE(zit[0].second == 10);
    REQUIRE(zit[1].first == 3);
    REQUIRE(zit[1].second == 2);
  }

  SECTION("test find in runtime") {
    for (const auto& p : z) {
      auto it = z.find(p.first);
      REQUIRE(it != z.end());
      REQUIRE(it->first == p.first);
      REQUIRE(it->second == p.second);
      REQUIRE(z[p.first] == p.second);
    }
  }
}

TEST_CASE("solid unordered_set", "[unordered_set]") {
  SECTION("each is unique with seed of 0.") {
    constexpr int a[] = {0, 1, 2, 3, 4};
    constexpr auto d = solid::make_ordered_set(a);
    static_assert(d.size() == 5);
    static_assert(d.contains(0));
    static_assert(d.contains(1));
    static_assert(d.contains(2));
    static_assert(d.contains(3));
    static_assert(d.contains(4));
    static_assert(!d.contains(5));
    static_assert(!d.contains(6));

    SECTION("test contains in runtime") {
      for (const auto& i : solid::array<int, 5>{0, 1, 2, 3, 4}) {
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
}

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
      for (const auto& i : solid::array<int, 5>{0, 1, 2, 3, 4}) {
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
      for (const auto& i : solid::array<int, 7>{0, 1, 2, 15, 5, 7, 6}) {
        REQUIRE(d.contains(i));
      }
    }
  }
}

TEST_CASE("solid bitset", "[bitset]") {
  SECTION("") {
    solid::bitset<100> bs;
    REQUIRE(bs.count() == 0);
    bs.set(77);
    REQUIRE(bs.count() == 1);
    REQUIRE(bs.test(77));
    bs.reset(77);
    REQUIRE(bs.count() == 0);
    REQUIRE(!bs.test(77));
  }
}

TEST_CASE("solid lens", "[lens]") {
  SECTION("") {
    constexpr solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
    constexpr auto get_first = [](const auto& p) { return p.first; };

    static_assert(
        std::is_same<decltype(make_lens(&a[0], get_first))::value_type,
                     int>::value);
    static_assert(*make_lens(&a[0], get_first) == 3);
    static_assert(*make_lens(&a[1], get_first) == 1);
  }

  SECTION("") {
    solid::pair<int, int> a[] = {{3, 2}, {1, 10}};
    auto get_first = [](auto& p) -> decltype(p.first)& { return p.first; };

    static_assert(
        std::is_same<decltype(make_lens(&a[0], get_first))::value_type,
                     int&>::value);
    for (auto it = make_lens(&a[0], get_first);
         it != make_lens(&a[2], get_first); ++it) {
      (*it)++;
    }

    REQUIRE(a[0].first == 4);
    REQUIRE(a[0].second == 2);
    REQUIRE(a[1].first == 2);
    REQUIRE(a[1].second == 10);
  }
}

TEST_CASE("solid unordered_map", "[unordered_map]") {
  constexpr solid::pair<int, int> a[] = {{4, 2}, {1, 10}};
  constexpr auto z = solid::make_unordered_map(a);
  // constexpr solid::unordered_map<int, int, 2> z = {{4, 2}, {1, 10}};
  static_assert(
      std::is_same<decltype(z)::value_type, solid::pair<int, int>>::value);
  // constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
  static_assert(z[4] == 2);
  static_assert(z[1] == 10);
  static_assert(z.find(4) != z.end());
  static_assert(z.find(4)->first == 4);
  static_assert(z.find(4)->second == 2);
  static_assert(z.find(1) != z.end());
  static_assert(z.find(1)->first == 1);
  static_assert(z.find(1)->second == 10);
  static_assert(z.find(100) == z.end());

  SECTION("test find in runtime") {
    for (const auto& p : z) {
      auto it = z.find(p.first);
      REQUIRE(it != z.end());
      REQUIRE(it->first == p.first);
      REQUIRE(it->second == p.second);
      REQUIRE(z[p.first] == p.second);
    }
  }
}
