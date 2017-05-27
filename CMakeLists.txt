cmake_minimum_required(VERSION 3.7)
project(const_map)

add_executable(const_map const_map.cpp)

list(APPEND CMAKE_CXX_FLAGS -std=gnu++1z)

# set_property(TARGET const_map PROPERTY CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# set_property(TARGET const_map PROPERTY CXX_STANDARD 14)

message(STATUS CXX=${CXX})
