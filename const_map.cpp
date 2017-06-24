#include <iostream>
#include <boost/hana.hpp>

#include <const_map.hpp>

using namespace std;

namespace hana = boost::hana;
using namespace hana::literals;

template<typename>
struct show_type;

int main() {
  int i = 3;
  const_sorted_map<int, 3, 1, 2> csm;
  cout << csm.index_of(1) << '\n';
  cout << csm.index_of(i) << '\n';
  static_assert(csm.index_of(hana::int_c<2>) == 1);
  return 0;
}
