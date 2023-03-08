// Copyright 2023 Klemens Morgenstern
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/system/result.hpp>
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>
#include <string>

using namespace boost::system;

struct XM
{
    int v_;

    explicit XM( int v = 0 ): v_( v ) {}

    XM( XM const& ) = delete;
    XM& operator=( XM const& ) = delete;
    XM( XM && ) = default;
    XM& operator=( XM && ) = default;
};

int main()
{
    {
        result<std::string, XM> r( 1 );

        BOOST_TEST( !r.has_value() );
        BOOST_TEST( r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 1 );
    }

    {
        BOOST_TEST(( !result<std::string, XM>( 1 ).has_value() ));
        BOOST_TEST(( result<std::string, XM>( 1 ).has_error() ));

        BOOST_TEST_EQ( (result<std::string, XM>( 1 ).error().v_), 1 );
    }

    {
        result<std::string, XM> r( "s" );

        BOOST_TEST( r.has_value() );
        BOOST_TEST( !r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 0 );
    }

    {
        result<std::string, XM> r( "s" );

        BOOST_TEST( r.has_value() );
        BOOST_TEST( !r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 0 );
    }

    {
        BOOST_TEST(( result<std::string, XM>( "s" ).has_value() ));
        BOOST_TEST(( !result<std::string, XM>( "s" ).has_error() ));

        BOOST_TEST_EQ( (result<std::string, XM>( "s" ).error().v_), 0 );
    }

      {
        result<void, XM> r( 1 );

        BOOST_TEST( !r.has_value() );
        BOOST_TEST( r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 1 );
    }

    {
        BOOST_TEST(( !result<void, XM>( 1 ).has_value() ));
        BOOST_TEST(( result<void, XM>( 1 ).has_error() ));

        BOOST_TEST_EQ( (result<void, XM>( 1 ).error().v_), 1 );
    }

    {
        result<void, XM> r;

        BOOST_TEST( r.has_value() );
        BOOST_TEST( !r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 0 );
    }

    {
        result<void, XM> r;

        BOOST_TEST( r.has_value() );
        BOOST_TEST( !r.has_error() );

        BOOST_TEST_EQ( std::move( r ).error().v_, 0 );
    }

    {
        BOOST_TEST(( result<void, XM>( ).has_value() ));
        BOOST_TEST(( !result<void, XM>( ).has_error() ));

        BOOST_TEST_EQ( (result<void, XM>( ).error().v_), 0 );
    }
    return boost::report_errors();
}
