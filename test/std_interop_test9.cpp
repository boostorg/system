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

enum my_errc
{
    my_enoent = ENOENT
};

template<> struct boost::system::is_error_code_enum<my_errc>: std::true_type {};
template<> struct std::is_error_code_enum<my_errc>: std::true_type {};

boost::system::error_code make_error_code( my_errc e )
{
    return boost::system::error_code( e, boost::system::generic_category() );
}

int main()
{
    {
        boost::system::error_code e1 = my_enoent;

        BOOST_TEST( e1 == my_enoent );
        BOOST_TEST_NOT( e1 != my_enoent );
    }

    {
        std::error_code e1 = my_enoent;

        BOOST_TEST( e1 == my_enoent );
        BOOST_TEST_NOT( e1 != my_enoent );
    }

    return boost::report_errors();
}

#endif
