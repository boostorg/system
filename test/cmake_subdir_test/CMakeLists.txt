# Copyright 2018-2021 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.5...3.20)

project(cmake_subdir_test LANGUAGES CXX)

add_subdirectory(../.. boostorg/system)
add_subdirectory(../../../assert boostorg/assert)
add_subdirectory(../../../config boostorg/config)
add_subdirectory(../../../core boostorg/core)
add_subdirectory(../../../mp11 boostorg/mp11)
add_subdirectory(../../../predef boostorg/predef)
add_subdirectory(../../../static_assert boostorg/static_assert)
add_subdirectory(../../../throw_exception boostorg/throw_exception)
add_subdirectory(../../../variant2 boostorg/variant2)
add_subdirectory(../../../winapi boostorg/winapi)

add_executable(quick ../quick.cpp)
target_link_libraries(quick Boost::system Boost::core)

enable_testing()
add_test(quick quick)

add_custom_target(check VERBATIM COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --no-tests=error -C $<CONFIG>)
