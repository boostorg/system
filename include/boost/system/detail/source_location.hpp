#ifndef BOOST_SYSTEM_DETAIL_SOURCE_LOCATION_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_SOURCE_LOCATION_HPP_INCLUDED

//  Copyright Beman Dawes 2006, 2007
//  Copyright Christoper Kohlhoff 2007
//  Copyright Peter Dimov 2017-2021
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  See library home page at http://www.boost.org/libs/system

#include <boost/system/detail/config.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>

namespace boost
{

namespace system
{

namespace detail
{

class source_location_ptr
{
public:

    BOOST_SYSTEM_CONSTEXPR source_location_ptr() BOOST_NOEXCEPT:
        value_( 0u )
    {
    }

    // Implicit (converting) constructor to allow passing source_location const* to error_code ctors and modifiers.
    BOOST_SYSTEM_IMPLICIT source_location_ptr( source_location const* ptr ) BOOST_NOEXCEPT:
        value_( reinterpret_cast<boost::uintptr_t>( ptr ) )
    {
    }

    BOOST_SYSTEM_CONSTEXPR boost::uintptr_t value() const BOOST_NOEXCEPT
    {
        return value_;
    }

private:

    boost::uintptr_t value_;

};

} // namespace detail

} // namespace system

} // namespace boost

#if defined(BOOST_DISABLE_CURRENT_LOCATION)

# define BOOST_SYSTEM_CURRENT_LOCATION_PTR ::boost::system::detail::source_location_ptr()

#elif defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L && defined(BOOST_GCC)

// gcc __builtin_source_location() returns std::source_location::__impl const* cast to void const*; we test that
// boost::source_location is layout-compatible with std::source_location::__impl, avoiding UB via memcpy.
# define BOOST_SYSTEM_CURRENT_LOCATION_PTR ::boost::system::detail::source_location_ptr( \
    static_cast<::boost::source_location const*>( __builtin_source_location() ) )

#elif defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L && defined(BOOST_CLANG)

// Clang __builtin_source_location() returns std::source_location::__impl const*; same considerations as gcc.
# define BOOST_SYSTEM_CURRENT_LOCATION_PTR ::boost::system::detail::source_location_ptr( \
    reinterpret_cast<::boost::source_location const*>( __builtin_source_location() ) )

#elif (defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L) \
    || (defined(BOOST_MSVC) && BOOST_MSVC >= 1926) \
    || (defined(BOOST_CLANG) && BOOST_CLANG_VERSION >= 90000 && !defined(BOOST_NO_CXX11_LAMBDAS)) \
    || (defined(BOOST_GCC) && BOOST_GCC >= 50000 && !defined(BOOST_NO_CXX11_LAMBDAS))

// BOOST_CURRENT_LOCATION has function_name(), so we have to collect it outside the lambda.
# define BOOST_SYSTEM_CURRENT_LOCATION_PTR ::boost::system::detail::source_location_ptr( \
    []( ::boost::source_location loc )                                                   \
    {                                                                                    \
        static const ::boost::source_location loc_ = loc;                                \
        return &loc_;                                                                    \
    }( BOOST_CURRENT_LOCATION ) )

#elif defined(BOOST_NO_CXX11_LAMBDAS)

// Not implementable without C++11 lambdas.
# define BOOST_SYSTEM_NO_CURRENT_LOCATION_PTR 1

#else

// no function_name(), so it's OK to collect BOOST_CURRENT_LOCATION inside the lambda.
# define BOOST_SYSTEM_CURRENT_LOCATION_PTR ::boost::system::detail::source_location_ptr( \
    []()                                                                                 \
    {                                                                                    \
        static BOOST_SYSTEM_CONSTEXPR ::boost::source_location loc_ = BOOST_CURRENT_LOCATION; \
        return &loc_;                                                                    \
    }() )

#endif

#endif // #ifndef BOOST_SYSTEM_DETAIL_SOURCE_LOCATION_HPP_INCLUDED
