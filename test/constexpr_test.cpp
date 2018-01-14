
// Copyright 2018 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.

#include <boost/system/error_code.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/config/pragma_message.hpp>
#include <boost/static_assert.hpp>

#if !defined(BOOST_SYSTEM_HAS_CONSTEXPR)

BOOST_PRAGMA_MESSAGE("Skipping constexpr test, BOOST_SYSTEM_HAS_CONSTEXPR isn't defined")
int main() {}

#else

using namespace boost::system;

constexpr error_code e1( 1, system_category() );

BOOST_STATIC_ASSERT( e1.value() == 1 );
BOOST_STATIC_ASSERT( e1.category() == system_category() );

constexpr error_code e2( 2, generic_category() );

BOOST_STATIC_ASSERT( e2.value() == 2 );
BOOST_STATIC_ASSERT( e2.category() == generic_category() );

int main()
{
    error_code e1_( 1, system_category() );
    BOOST_TEST_EQ( e1, e1_ );

    error_code e2_( 2, generic_category() );
    BOOST_TEST_EQ( e2, e2_ );

    return boost::report_errors();
}

#endif
