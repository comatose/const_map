cmake_minimum_required(VERSION 3.7)
project(const_map)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(Hana_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/ext/hana")
find_package(Hana 1.1.0)

add_executable(const_map const_map.cpp)
add_dependencies(const_map Hana)

add_executable(solid solid.cpp)
add_dependencies(solid Hana)

include_directories(
  "${CMAKE_SOURCE_DIR}/include"
  ${Hana_INCLUDE_DIRS}
)
list(APPEND CMAKE_CXX_FLAGS "-std=gnu++1z -O3")

# set_property(TARGET const_map PROPERTY CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# set_property(TARGET const_map PROPERTY CXX_STANDARD 14)
