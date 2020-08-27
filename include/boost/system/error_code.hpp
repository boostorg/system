#ifndef BOOST_SYSTEM_ERROR_CODE_HPP_INCLUDED
#define BOOST_SYSTEM_ERROR_CODE_HPP_INCLUDED

//  Copyright Beman Dawes 2006, 2007
//  Copyright Christoper Kohlhoff 2007
//  Copyright Peter Dimov 2017, 2018
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  See library home page at http://www.boost.org/libs/system

#include <boost/system/detail/error_code.hpp>
#include <boost/system/error_category.hpp>
#include <boost/system/error_condition.hpp>
#include <boost/system/errc.hpp>
#include <boost/system/detail/generic_category.hpp>
#include <boost/system/detail/system_category.hpp>
#include <boost/system/detail/throws.hpp>
#include <boost/system/api_config.hpp>
#include <boost/system/detail/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <ostream>
#include <string>
#include <functional>
#include <cstring>

#if defined(BOOST_SYSTEM_HAS_SYSTEM_ERROR)
# include <system_error>
#endif

#if !defined(BOOST_POSIX_API) && !defined(BOOST_WINDOWS_API)
#  error BOOST_POSIX_API or BOOST_WINDOWS_API must be defined
#endif

namespace boost
{

namespace system
{

class error_code;         // values defined by the operating system
class error_condition;    // portable generic values defined below, but ultimately
                          // based on the POSIX standard

}  // namespace system

// non-member functions of error_code and error_condition

namespace system
{

inline bool operator==( const error_code & code, const error_condition & condition ) BOOST_NOEXCEPT
{
    return code.category().equivalent( code.value(), condition ) || condition.category().equivalent( code, condition.value() );
}

inline bool operator!=( const error_code & lhs, const error_condition & rhs ) BOOST_NOEXCEPT
{
    return !( lhs == rhs );
}

inline bool operator==( const error_condition & condition, const error_code & code ) BOOST_NOEXCEPT
{
    return code.category().equivalent( code.value(), condition ) || condition.category().equivalent( code, condition.value() );
}

inline bool operator!=( const error_condition & lhs, const error_code & rhs ) BOOST_NOEXCEPT
{
    return !( lhs == rhs );
}

} // namespace system

} // namespace boost

// system_error_category implementation

#if defined(BOOST_WINDOWS_API)

#include <boost/system/detail/system_category_win32.hpp>

inline boost::system::error_condition boost::system::detail::system_error_category::default_error_condition( int ev ) const BOOST_NOEXCEPT
{
    return system_category_default_error_condition_win32( ev );
}

inline std::string boost::system::detail::system_error_category::message( int ev ) const
{
    return system_category_message_win32( ev );
}

inline char const * boost::system::detail::system_error_category::message( int ev, char * buffer, std::size_t len ) const BOOST_NOEXCEPT
{
    return system_category_message_win32( ev, buffer, len );
}

#else // #if defined(BOOST_WINDOWS_API)

#include <boost/system/detail/system_category_posix.hpp>

inline boost::system::error_condition boost::system::detail::system_error_category::default_error_condition( int ev ) const BOOST_NOEXCEPT
{
    return system_category_default_error_condition_posix( ev );
}

inline std::string boost::system::detail::system_error_category::message( int ev ) const
{
    return generic_error_category_message( ev );
}

inline char const * boost::system::detail::system_error_category::message( int ev, char * buffer, std::size_t len ) const BOOST_NOEXCEPT
{
    return generic_error_category_message( ev, buffer, len );
}

#endif // #if defined(BOOST_WINDOWS_API)

#endif // BOOST_SYSTEM_ERROR_CODE_HPP_INCLUDED
