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
  linux_cxx("TOOLSET=gcc COMPILER=g++ CXXSTD=03,11,14 ADDR Job 0", "g++", packages="g++-multilib", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++', 'CXXSTD': '03,11,14', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': 'b6589fc6ab'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc COMPILER=g++ CXXSTD=03,11,14 ADDR Job 1", "g++", packages="", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++', 'CXXSTD': '03,11,14', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': '356a192b79'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc COMPILER=g++ CXXSTD=03,11,14 Job 2", "g++", packages="", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++', 'CXXSTD': '03,11,14', 'DRONE_JOB_UUID': 'da4b9237ba'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc COMPILER=g++ CXXSTD=03,11,14 ADDR Job 3", "g++", packages="", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++', 'CXXSTD': '03,11,14', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': '77de68daec'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc COMPILER=g++-4.4 CXXSTD=98,0x Job 4", "g++", packages="g++-4.4", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++-4.4', 'CXXSTD': '98,0x', 'DRONE_JOB_UUID': '1b64538924'}, globalenv=globalenv),
  linux_cxx("TOOLSET=gcc COMPILER=g++-4.6 CXXSTD=03,0x Job 5", "g++", packages="g++-4.6", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'TOOLSET': 'gcc', 'COMPILER': 'g++-4.6', 'CXXSTD': '03,0x', 'DRONE_JOB_UUID': 'ac3478d69a'}, globalenv=globalenv),
  linux_cxx("UBSAN=1 TOOLSET=gcc COMPILER=g++-10 CXXSTD=03 Job 6", "g++-10", packages="g++-10", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1804:1", environment={'UBSAN': '1', 'TOOLSET': 'gcc', 'COMPILER': 'g++-10', 'CXXSTD': '03,11,14,17,20', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'LINKFLAGS': '-fuse-ld=gold', 'DRONE_JOB_UUID': 'c1dfd96eea'}, globalenv=globalenv),
  linux_cxx("TOOLSET=clang COMPILER=/usr/bin/clang++ CXXST Job 7", "/usr/bin/clang++", packages="clang-3.3", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1404:1", environment={'TOOLSET': 'clang', 'COMPILER': '/usr/bin/clang++', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': '902ba3cda1'}, globalenv=globalenv),
  linux_cxx("TOOLSET=clang COMPILER=/usr/bin/clang++ CXXST Job 8", "/usr/bin/clang++", packages="clang-3.4", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1404:1", environment={'TOOLSET': 'clang', 'COMPILER': '/usr/bin/clang++', 'CXXSTD': '03,11', 'DRONE_JOB_UUID': 'fe5dbbcea5'}, globalenv=globalenv),
  linux_cxx("UBSAN=1 TOOLSET=clang COMPILER=clang++-11 CXX Job 9", "clang++-11", packages="clang-11", llvm_os="xenial", llvm_ver="11", buildtype="boost", buildscript="drone", image=linuxglobalimage, environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++-11', 'CXXSTD': '03,11,14,17,20', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': '0ade7c2cf9'}, globalenv=globalenv),
  linux_cxx("UBSAN=1 TOOLSET=clang COMPILER=clang++-libc++ Job 10", "clang++-libc++", packages="libc++-dev", buildtype="boost", buildscript="drone", image="cppalliance/droneubuntu1804:1", environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++-libc++', 'CXXSTD': '03,11,14,17,2a', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': 'b1d5781111'}, globalenv=globalenv),
  osx_cxx("TOOLSET=clang COMPILER=clang++ CXXSTD=03,11,1 Job 12", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="7.3", environment={'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': '7b52009b64'}, globalenv=globalenv),
  osx_cxx("TOOLSET=clang COMPILER=clang++ CXXSTD=03,11,1 Job 13", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="8.3", environment={'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': 'bd307a3ec3'}, globalenv=globalenv),
  osx_cxx("TOOLSET=clang COMPILER=clang++ CXXSTD=03,11,1 Job 14", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="9.4", environment={'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'ADDRMD': '32,64', 'DRONE_JOB_UUID': 'fa35e19212'}, globalenv=globalenv),
  osx_cxx("TOOLSET=clang COMPILER=clang++ CXXSTD=03,11,1 Job 15", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="10.1", environment={'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'DRONE_JOB_UUID': 'f1abd67035'}, globalenv=globalenv),
  osx_cxx("TOOLSET=clang COMPILER=clang++ CXXSTD=03,11,1 Job 16", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="11.3", environment={'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'DRONE_JOB_UUID': '1574bddb75'}, globalenv=globalenv),
  osx_cxx("UBSAN=1 TOOLSET=clang COMPILER=clang++ CXXSTD Job 17", "clang++", packages="", buildtype="boost", buildscript="drone", xcode_version="12.2", environment={'UBSAN': '1', 'TOOLSET': 'clang', 'COMPILER': 'clang++', 'CXXSTD': '03,11,14,1z', 'UBSAN_OPTIONS': 'print_stacktrace=1', 'DRONE_JOB_UUID': '0716d9708d'}, globalenv=globalenv),
  linux_cxx("CMAKE=1 Job 18", "g++", packages="", buildtype="aa8f93b806-b342e8ae9b", buildscript="drone", image=linuxglobalimage, environment={'CMAKE': '1', 'DRONE_JOB_UUID': '9e6a55b6b4'}, globalenv=globalenv),
  linux_cxx("CMAKE=1 BUILD_SHARED_LIBS=ON Job 19", "g++", packages="", buildtype="aa8f93b806-0b4c708508", buildscript="drone", image=linuxglobalimage, environment={'CMAKE': '1', 'BUILD_SHARED_LIBS': 'ON', 'DRONE_JOB_UUID': 'b3f0c7f6bb'}, globalenv=globalenv),
  linux_cxx("CMAKE_SUBDIR_TEST=1 Job 20", "g++", packages="", buildtype="5e4a4d0f23-fda7c76df5", buildscript="drone", image=linuxglobalimage, environment={'CMAKE_SUBDIR_TEST': '1', 'DRONE_JOB_UUID': '91032ad7bb'}, globalenv=globalenv),
  linux_cxx("CMAKE_INSTALL=1 Job 21", "g++", packages="", buildtype="aa8f93b806-e569545176", buildscript="drone", image=linuxglobalimage, environment={'CMAKE_INSTALL': '1', 'DRONE_JOB_UUID': '472b07b9fc'}, globalenv=globalenv),
    ]

# from https://github.com/boostorg/boost-ci
load("@boost_ci//ci/drone/:functions.star", "linux_cxx","windows_cxx","osx_cxx","freebsd_cxx")
