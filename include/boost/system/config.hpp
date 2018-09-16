#ifndef BOOST_SYSTEM_CONFIG_HPP_INCLUDED
#define BOOST_SYSTEM_CONFIG_HPP_INCLUDED

// Copyright Beman Dawes 2003, 2006
// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/system for documentation.

// This header is no longer used by Boost.System.
// Its use is discouraged and it will be deprecated.

#include <boost/config.hpp>

// Included for compatibility. Not used.
#include <boost/system/api_config.hpp>

// Definition of BOOST_SYSTEM_DECL retained for compatibility.

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SYSTEM_DYN_LINK)
# if defined(BOOST_SYSTEM_SOURCE)
#   define BOOST_SYSTEM_DECL BOOST_SYMBOL_EXPORT
# else 
#   define BOOST_SYSTEM_DECL BOOST_SYMBOL_IMPORT
# endif
#else
# define BOOST_SYSTEM_DECL
#endif

#endif // BOOST_SYSTEM_CONFIG_HPP_INCLUDED
