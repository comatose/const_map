cmake_minimum_required(VERSION 3.7)
project(const_map)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set(Hana_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/ext/hana")
find_package(Hana 1.1.0)

add_executable(const_map const_map.cpp)
add_dependencies(const_map Hana)

target_include_directories(const_map PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${Hana_INCLUDE_DIRS}"
)
add_executable(solid tests-main.cpp tests-solid.cpp)
add_dependencies(solid Hana)

target_include_directories(solid PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/Catch/include"
)

list(APPEND CMAKE_CXX_FLAGS "-std=gnu++1z -O3")

# set_property(TARGET const_map PROPERTY CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# set_property(TARGET const_map PROPERTY CXX_STANDARD 14)
