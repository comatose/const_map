#include "catch.hpp"

#include "solid.hpp"

TEST_CASE("solid array", "[array]") {
  constexpr solid::array<int, 5> a = {3, 1, 10, 4, 8};
  static_assert(a[0] == 3 && a[1] == 1 && a[2] == 10 && a[3] == 4 && a[4] == 8);
  static_assert(a.size() == 5);

  // number of initial values should be less than or equal to the length of
  // array.
  constexpr solid::array<int, 6> a1 = {3, 1, 10, 4, 8};
  static_assert(a1[0] == 3 && a1[1] == 1 && a1[2] == 10 && a1[3] == 4 &&
                a1[4] == 8);
  static_assert(a1[5] == int{});
  static_assert(a1.size() == 6);

  // the following causes error.
  //  constexpr solid::array<int, 4> a2 = {3, 1, 10, 4, 8};

  constexpr auto a2 = quick_sort(a);
  static_assert(a2[0] == 1 && a2[1] == 3 && a2[2] == 4 && a2[3] == 8 &&
                a2[4] == 10);
  static_assert(a2.size() == 5);

  constexpr solid::array<int, 5> a3(a.begin(), a.end());
  static_assert(a3[0] == 3 && a3[1] == 1 && a3[2] == 10 && a3[3] == 4 &&
                a3[4] == 8);
  static_assert(a3.size() == 5);

  constexpr solid::array<solid::pair<int, int>, 2> a4 = {{1, 2}, {3, 10}};
  static_assert(a4.size() == 2);

  constexpr int c[] = {3, 1, 10, 4, 8};
  constexpr auto a5 = solid::make_array(c);
  static_assert(a5.size() == 5);
  static_assert(a5[0] == 3 && a5[1] == 1 && a5[2] == 10 && a5[3] == 4 &&
                a5[4] == 8);

  constexpr auto a6 = solid::append(a5, 9);
  static_assert(a6.size() == 6);
  static_assert(a6[0] == 3 && a6[1] == 1 && a6[2] == 10 && a6[3] == 4 &&
                a6[4] == 8);
  static_assert(a6[5] == 9);
  static_assert(std::tuple_size<decltype(a6)>::value == 6);
}
