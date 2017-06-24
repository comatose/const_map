#include <iostream>
#include <cassert>

#include <solid.hpp>

using namespace std;

template<typename>
struct show_type;

int main() {
  constexpr solid::array<int, 5> a = {3, 1, 10, 4, 8};
  constexpr auto g = quick_sort(a);
  static_assert(g[0] == 1 && g[1] == 3 && g[2] == 4 && g[3] == 8 && g[4] == 10);

  constexpr solid::ordered_set<int, 5> b = {3, 1, 10, 4, 8};
  static_assert(b.contains(3) && b.contains(1) && b.contains(10) && b.contains(4) && b.contains(8));
  static_assert(!b.contains(30) && !b.contains(40) && !b.contains(100));
  auto bit = b.cbegin();
  assert(bit[0] == 1 && bit[1] == 3 && bit[2] == 4 && bit[3] == 8 && bit[4] == 10);

  int i = 3;
  assert(b.contains(i));

  constexpr solid::array<int, 5> c(b.begin(), b.end());
  constexpr solid::array<solid::pair<int, int>, 2> k = {{1, 2}, {3, 10}};

  constexpr solid::ordered_map<int, int, 2> z = {{3, 2}, {1, 10}};
  static_assert(z[3] == 2 && z[1] == 10);
  assert(z[i] == 2);

  static_assert(solid::hash<int>{}(1) == 1);

  constexpr solid::unordered_set<int, 5> d = {0, 1, 2, 3, 4};
  static_assert(d.contains(0));
  static_assert(d.contains(1));
  static_assert(d.contains(2));
  static_assert(d.contains(3));
  static_assert(!d.contains(5));
  static_assert(!d.contains(6));

  solid::unordered_set<int, 5> f = {0, 1, 2, i, 4};
  assert(f.contains(i));
  assert(!f.contains(i*100));

  return 0;
}
