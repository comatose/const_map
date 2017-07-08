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

target_compile_options(const_map PRIVATE -std=gnu++1z -O3)

add_executable(solid tests-main.cpp tests-solid.cpp)

target_include_directories(solid PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
)

target_include_directories(solid PRIVATE
  "${CMAKE_SOURCE_DIR}/Catch/include"
)

target_compile_options(solid PRIVATE -std=gnu++1z -O3 -fconstexpr-steps=10000000 -fconstexpr-depth=1000)

# set_property(TARGET const_map PROPERTY CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# set_property(TARGET const_map PROPERTY CXX_STANDARD 14)
