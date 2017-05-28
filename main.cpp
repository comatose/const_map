#include <iostream>
#include <boost/hana.hpp>

#include <solid.hpp>

using namespace std;

namespace hana = boost::hana;
using namespace hana::literals;

template<typename>
struct show_type;

int main() {
  constexpr solid::array<int, 5> a = {3, 1, 10, 4, 8};
  constexpr auto g = quick_sort(a);
  static_assert(g[0] == 1 && g[1] == 3 && g[2] == 4 && g[3] == 8 && g[4] == 10);

  constexpr solid::ordered_set<int, 5> b = {3, 1, 10, 4, 8};
  static_assert(b[0] == 1 && b[1] == 3 && b[2] == 4 && b[3] == 8 && b[4] == 10);

  static_assert(b.find(1) == &b[0] && b.find(3) == &b[1] && b.find(4) == &b[2] &&
                b.find(8) == &b[3] && b.find(10) == &b[4]);

  int i = 3;
  cout << b.find(i) - b.begin() << '\n';
  return 0;
}
