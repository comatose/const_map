cmake_minimum_required(VERSION 3.7)
project(Solid)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")
# set(Hana_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/ext/hana")
# find_package(Hana 1.1.0)

add_library(Solid INTERFACE)
target_include_directories(Solid INTERFACE "include")
target_compile_options(Solid INTERFACE -std=gnu++1z)

add_executable(test_solid
  test/tests-main.cpp
  test/tests-array.cpp
  test/tests-bitset.cpp
  test/tests-lens.cpp
  test/tests-ordered_map.cpp
  test/tests-ordered_set.cpp
  test/tests-stack.cpp
  test/tests-table_indexer.cpp
  test/tests-unordered_map.cpp
  test/tests-unordered_set.cpp
)
target_link_libraries(test_solid Solid)
target_include_directories(test_solid PUBLIC ${CATCH_INCLUDE_DIR})
target_compile_options(test_solid PRIVATE -O3)

file(GLOB_RECURSE all_source_files "include/*[ch]pp" "tests-*.cpp")

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT AND all_source_files)
  message(STATUS "FOUND clang-format.")
  add_custom_target(clang-format ALL ${CLANG_FORMAT} -style=Google -sort-includes -i ${all_source_files})
endif()

# target_compile_options(Solid PRIVATE -std=gnu++1z -O3 -fconstexpr-steps=10000000 -fconstexpr-depth=1000)

# set_property(TARGET Solid PROPERTY CXX_INCLUDE_WHAT_YOU_USE "iwyu")
# set_property(TARGET Solid PROPERTY CXX_STANDARD 14)
