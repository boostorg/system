#ifndef BOOST_SYSTEM_DETAIL_CONFIG_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_CONFIG_HPP_INCLUDED

// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/system for documentation.

#include <boost/config.hpp>

// BOOST_SYSTEM_HAS_SYSTEM_ERROR

#if !defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)
# define BOOST_SYSTEM_HAS_SYSTEM_ERROR
#endif

#if defined(BOOST_MSVC) && BOOST_MSVC < 1700
// msvc-10.0 has no two-argument map::emplace
# undef BOOST_SYSTEM_HAS_SYSTEM_ERROR
#endif

// BOOST_SYSTEM_NOEXCEPT
// Retained for backward compatibility only

#define BOOST_SYSTEM_NOEXCEPT BOOST_NOEXCEPT

// BOOST_SYSTEM_HAS_CONSTEXPR

#if !defined(BOOST_NO_CXX14_CONSTEXPR)
# define BOOST_SYSTEM_HAS_CONSTEXPR
#endif

#if defined(__GNUC__) && (__GNUC__ == 7 && __GNUC_MINOR__ < 4) && __cplusplus >= 201700L
// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=83835
#  undef BOOST_SYSTEM_HAS_CONSTEXPR
#endif

#if defined(__clang__) && defined(_MSC_VER) && defined(_CPPLIB_VER)
// Clang on Windows with MSVC headers, the constructor of std::error_category
// is not constexpr at least up to VS2017 15.7.x (_MSVC_STL_UPDATE 201803)
#  undef BOOST_SYSTEM_HAS_CONSTEXPR
#endif

#if defined(__clang__) && defined(BOOST_LIBSTDCXX_VERSION) && BOOST_LIBSTDCXX_VERSION < 40900
// The constructor of std::error_category is not constexpr in libstdc++ 4.8
#  undef BOOST_SYSTEM_HAS_CONSTEXPR
#endif

#if defined(BOOST_SYSTEM_HAS_CONSTEXPR)
# define BOOST_SYSTEM_CONSTEXPR constexpr
#else
# define BOOST_SYSTEM_CONSTEXPR
#endif

// BOOST_SYSTEM_REQUIRE_CONST_INIT

#define BOOST_SYSTEM_REQUIRE_CONST_INIT

#if defined(__has_cpp_attribute)
#if __has_cpp_attribute(clang::require_constant_initialization)
# undef BOOST_SYSTEM_REQUIRE_CONST_INIT
# define BOOST_SYSTEM_REQUIRE_CONST_INIT [[clang::require_constant_initialization]]
#endif
#endif

#endif // BOOST_SYSTEM_DETAIL_CONFIG_HPP_INCLUDED
