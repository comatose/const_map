#include <const_map.hpp>
#include <value_sequence.hpp>

#include <iostream>

#include <boost/hana.hpp>

namespace hana = boost::hana;
using namespace hana::literals;

template<typename>
struct show_type;

using namespace std;

int main() {
  auto m = make_const_sorted_map(3_c, 2_c, 10_c);
  cout << m.index_of(2) << '\n';
  cout << m.index_of(3) << '\n';
  cout << m.index_of(10) << '\n';
  cout << m.index_of(100) << '\n';
  return 0;
}
