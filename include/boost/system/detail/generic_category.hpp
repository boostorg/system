// Implementation details of generic_error_category
//
// Copyright 2018 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See library home page at http://www.boost.org/libs/system

#include <cstring>

namespace boost
{

namespace system
{

namespace detail
{

#if defined(__GLIBC__)

// std::strerror is not thread-safe on glibc (for no reason)
// glibc also has two incompatible strerror_r definitions (for no reason)

inline char const * strerror_r_helper( char const * r, char const * )
{
    return r;
}

inline char const * strerror_r_helper( int r, char const * buffer )
{
    return r == 0? buffer: "Unknown error";
}

inline std::string generic_error_category_message( int ev )
{
    char buffer[ 128 ];
    return strerror_r_helper( strerror_r( ev, buffer, sizeof( buffer ) ), buffer );
}

#else

// std::strerror is thread-safe on everything else, incl. Windows

inline std::string generic_error_category_message( int ev )
{

# if defined( BOOST_MSVC )
#  pragma warning( push )
#  pragma warning( disable: 4996 )
# endif

    char const * m = std::strerror( ev );

# if defined( BOOST_MSVC )
#  pragma warning( pop )
# endif

    return m? m: "Unknown error";

#endif
}

} // namespace detail

} // namespace system

} // namespace boost
