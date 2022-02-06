# Use, modification, and distribution are
# subject to the Boost Software License, Version 1.0. (See accompanying
# file LICENSE.txt)
#
# Copyright Rene Rivera 2020.

# For Drone CI we use the Starlark scripting language to reduce duplication.
# As the yaml syntax for Drone CI is rather limited.
#
#
globalenv={}
linuxglobalimage="cppalliance/droneubuntu1604:1"
windowsglobalimage="cppalliance/dronevs2019"

def main(ctx):
  return [
  linux_cxx("GCC 32/64 bit", "g++", packages="g++-multilib", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++', 'CXXSTD': '03,11,14', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': 'b6589fc6ab'}, globalenv=globalenv),
  linux_cxx("GCC 4.4", "g++", packages="g++-4.4", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++-4.4', 'CXXSTD': '98,0x', 'DRONE_JOB_UUID': '1b64538924'}, globalenv=globalenv),
  linux_cxx("GCC 4.6", "g++", packages="g++-4.6", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++-4.6', 'CXXSTD': '03,0x', 'DRONE_JOB_UUID': 'ac3478d69a'}, globalenv=globalenv),
  linux_cxx("GCC 10 UBSAN", "g++-10", packages="g++-10", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1804:1", environment={'UBSAN': '1', 'TOOLSET': 'gcc', 'COMPILER': 'g++-10', 'CXXSTD': '03,11,14,17,20', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'LINKFLAGS': '-fuse-ld=gold', 'DRONE_JOB_UUID': 'c1dfd96eea'}, globalenv=globalenv),
  linux_cxx("Clang 3.3", "/usr/bin/clang++", packages="clang-3.3", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1404:1", environment={'TOOLSET': 'clang', 'COMPILER': '/usr/bin/clang++', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '902ba3cda1'}, globalenv=globalenv),
  linux_cxx("Clang 3.4", "/usr/bin/clang++", packages="clang-3.4", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1404:1", environment={'TOOLSET': 'clang', 'COMPILER': '/usr/bin/clang++', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': 'fe5dbbcea5'}, globalenv=globalenv),
  linux_cxx("Clang 11 UBSAN", "clang++-11", packages="clang-11", llvm_os="xenial", llvm_ver="11", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++-11', 'CXXSTD': '03,11,14,17,20', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': '0ade7c2cf9'}, globalenv=globalenv),
  linux_cxx("Clang libc++ UBSAN", "clang++-libc++", packages="libc++-dev", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1804:1", environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++-libc++', 'CXXSTD': '03,11,14,17,2a', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': 'b1d5781111'}, globalenv=globalenv),
  osx_cxx("Clang UBSAN", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="12.2", environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': '0716d9708d'}, globalenv=globalenv),
  windows_cxx("msvc-14.0", "", image="cppalliance/dronevs2015", buildtype="boost", buildscript="drone", environment={"B2_TOOLSET": "msvc-14.0", "B2_CXXSTD": "14,latest"}, globalenv=globalenv),
  windows_cxx("msvc-14.1", "", image="cppalliance/dronevs2017", buildtype="boost", buildscript="drone", environment={"B2_TOOLSET": "msvc-14.1", "B2_CXXSTD": "14,17,latest"}, globalenv=globalenv),
  windows_cxx("msvc-14.2", "", image="cppalliance/dronevs2019", buildtype="boost", buildscript="drone", environment={"B2_TOOLSET": "msvc-14.2", "B2_CXXSTD": "14,17,20,latest"}, globalenv=globalenv),
  windows_cxx("msvc-14.3", "", image="cppalliance/dronevs2022:1", buildtype="boost", buildscript="drone", environment={"B2_TOOLSET": "msvc-14.3", "B2_CXXSTD": "14,17,20,latest"}, globalenv=globalenv)
    ]

# from https://github.com/boostorg/boost-ci
load("@boost_ci//ci/drone/:functions.star", "linux_cxx","windows_cxx","osx_cxx","freebsd_cxx")
