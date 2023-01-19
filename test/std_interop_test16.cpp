// Copyright 2023 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/system/detail/config.hpp>
#include <boost/config/pragma_message.hpp>

#if !defined(BOOST_SYSTEM_HAS_SYSTEM_ERROR)

BOOST_PRAGMA_MESSAGE( "BOOST_SYSTEM_HAS_SYSTEM_ERROR not defined, test will be skipped" )
int main() {}

#else

#include <boost/asio/error.hpp>
#include <boost/core/lightweight_test.hpp>
#include <system_error>

bool init_lwt = (boost::core::lwt_init(), true);

std::error_category const & cat = boost::asio::error::get_misc_category();

int main()
{
    BOOST_TEST_CSTR_EQ( cat.name(), "asio.misc" );
    return boost::report_errors();
}


#endif
