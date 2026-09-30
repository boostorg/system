// Copyright 2026 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/system/error_code.hpp>
#include <boost/system/error_condition.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config.hpp>
#include <boost/config/pragma_message.hpp>

#if defined(BOOST_NO_CXX20_HDR_FORMAT)

BOOST_PRAGMA_MESSAGE( "Test skipped because BOOST_NO_CXX20_HDR_FORMAT is defined" )
int main() {}

#else

namespace sys = boost::system;

int main()
{
    {
        sys::error_code ec;

        BOOST_TEST_EQ( std::format( "{}", ec ), "system:0" );
        BOOST_TEST_EQ( std::format( "{:_^12}", ec ), "__system:0__" );
    }

    {
        sys::error_code ec( 5, sys::generic_category() );

        BOOST_TEST_EQ( std::format( "{}", ec ), "generic:5" );
        BOOST_TEST_EQ( std::format( "{:_^12}", ec ), "_generic:5__" );
    }

    {
        sys::error_condition en;

        BOOST_TEST_EQ( std::format( "{}", en ), "cond:generic:0" );
        BOOST_TEST_EQ( std::format( "{:_^18}", en ), "__cond:generic:0__" );
    }

    {
        sys::error_condition en( 5, sys::system_category() );

        BOOST_TEST_EQ( std::format( "{}", en ), "cond:system:5" );
        BOOST_TEST_EQ( std::format( "{:_^18}", en ), "__cond:system:5___" );
    }

    return boost::report_errors();
}

#endif // defined(BOOST_NO_CXX20_HDR_FORMAT)
