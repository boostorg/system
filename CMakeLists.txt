# Copyright 2018 Mike Dev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.System is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)
project(BoostSystem)

add_library(boost_system INTERFACE)

add_library(Boost::system ALIAS boost_system)

target_include_directories(boost_system INTERFACE include)

target_link_libraries(boost_system
    INTERFACE
        Boost::config
        Boost::winapi
)

