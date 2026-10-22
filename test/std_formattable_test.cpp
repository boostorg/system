// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/system/error_code.hpp>
#include <boost/system/error_condition.hpp>
#include <boost/config.hpp>
#include <boost/config/pragma_message.hpp>

#if !defined(BOOST_NO_CXX20_HDR_FORMAT)
# include <format>
#endif

#if !( defined(__cpp_lib_format_ranges) && __cpp_lib_format_ranges >= 202207L )

BOOST_PRAGMA_MESSAGE( "Test skipped, because __cpp_lib_format_ranges is not >= 202207L" )

#else

static_assert( std::formattable<boost::system::error_code, char> );
static_assert( std::formattable<boost::system::error_condition, char> );

#endif // __cpp_lib_format_ranges
