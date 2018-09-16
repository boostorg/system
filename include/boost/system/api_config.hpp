#ifndef BOOST_SYSTEM_API_CONFIG_HPP_INCLUDED
#define BOOST_SYSTEM_API_CONFIG_HPP_INCLUDED

// Copyright Beman Dawes 2003, 2006, 2010
// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// See http://www.boost.org/LICENSE_1_0.txt
//
// See http://www.boost.org/libs/system for documentation.

// This header is no longer used by Boost.System.
// Its use is discouraged and it will be deprecated.

// Definition of BOOST_*_API retained for compatibility.

#if defined(_WIN32) || defined(__CYGWIN__)
// Windows default, including MinGW and Cygwin
#  define BOOST_WINDOWS_API
# else
#  define BOOST_POSIX_API
#endif
                                     
#endif  // BOOST_SYSTEM_API_CONFIG_HPP_INCLUDED
