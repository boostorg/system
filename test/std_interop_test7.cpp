// Copyright 2021 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/system/error_code.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config/pragma_message.hpp>
#include <cerrno>

#if !defined(BOOST_SYSTEM_HAS_SYSTEM_ERROR)

BOOST_PRAGMA_MESSAGE( "BOOST_SYSTEM_HAS_SYSTEM_ERROR not defined, test will be skipped" )
int main() {}

#else

#include <system_error>

int main()
{
    {
        boost::system::error_code e1 = make_error_code( boost::system::errc::bad_address );

        BOOST_TEST( e1 == boost::system::errc::bad_address );
        BOOST_TEST_NOT( e1 != boost::system::errc::bad_address );

        BOOST_TEST( e1 == std::errc::bad_address );
        BOOST_TEST_NOT( e1 != std::errc::bad_address );
    }

    {
        boost::system::error_code e1 = make_error_code( std::errc::bad_address );

        BOOST_TEST( e1 == boost::system::errc::bad_address );
        BOOST_TEST_NOT( e1 != boost::system::errc::bad_address );

        BOOST_TEST( e1 == std::errc::bad_address );
        BOOST_TEST_NOT( e1 != std::errc::bad_address );
    }

    return boost::report_errors();
}

#endif
