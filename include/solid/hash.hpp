#ifndef __SOLID_HASH_HPP
#define __SOLID_HASH_HPP

#include <cstddef>

namespace solid {

namespace internal {

template <typename T, class Hash = solid::hash<T>>
constexpr std::size_t hash_with(std::size_t d, const T& value) {
  return ((d * 0x01000193) ^ Hash{}(value)) & 0xffffffff;
}
}
}

#endif  // __SOLID_HASH_HPP
