
// Copyright 2017 Peter Dimov.
//
// Distributed under the Boost Software License, Version 1.0.
//
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt

// See library home page at http://www.boost.org/libs/system

#include <boost/config.hpp>

#if defined(BOOST_NO_CXX11_HDR_SYSTEM_ERROR)

int main() {}

#else

#include <boost/system/error_code.hpp>
#include <boost/core/lightweight_test.hpp>
#include <system_error>
#include <cerrno>
#include <string>

static void test_generic_category()
{
    int ev = ENOENT;

    // check whether the standard generic category works

    std::error_category const & st0 = std::generic_category();
    bool has_roundtrip = st0.equivalent( ev, st0.default_error_condition( ev ) );

    //

    boost::system::error_category const & bt = boost::system::generic_category();
    std::error_category const & st = bt;

    BOOST_TEST_CSTR_EQ( bt.name(), st.name() );

    if( has_roundtrip )
    {
        BOOST_TEST_EQ( &st, &std::generic_category() );
    }
    else
    {
        BOOST_TEST_EQ( bt.message( ev ), st.message( ev ) );
    }

    {
        boost::system::error_code bc( ev, bt );

        BOOST_TEST_EQ( bc.value(), ev );
        BOOST_TEST_EQ( &bc.category(), &bt );

        std::error_code sc( bc );

        BOOST_TEST_EQ( sc.value(), ev );
        BOOST_TEST_EQ( &sc.category(), &st );
    }

    {
        boost::system::error_condition bn = bt.default_error_condition( ev );

        BOOST_TEST_EQ( bn.value(), ev );
        BOOST_TEST_EQ( &bn.category(), &bt );

        BOOST_TEST( bt.equivalent( ev, bn ) );

        std::error_condition sn( bn );

        BOOST_TEST_EQ( sn.value(), ev );
        BOOST_TEST_EQ( &sn.category(), &st );

        BOOST_TEST( st.equivalent( ev, sn ) );
    }
}

static void test_system_category()
{
    boost::system::error_category const & bt = boost::system::system_category();
    std::error_category const & st = bt;

    BOOST_TEST_CSTR_EQ( bt.name(), st.name() );

    {
        int ev = 5;
        BOOST_TEST_EQ( bt.message( ev ), st.message( ev ) );

        {
            boost::system::error_code bc( ev, bt );

            BOOST_TEST_EQ( bc.value(), ev );
            BOOST_TEST_EQ( &bc.category(), &bt );

            std::error_code sc( bc );

            BOOST_TEST_EQ( sc.value(), ev );
            BOOST_TEST_EQ( &sc.category(), &st );
        }

        {
            boost::system::error_condition bn = bt.default_error_condition( ev );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }
    }

    {
        int ev = 4;
        BOOST_TEST_EQ( bt.message( ev ), st.message( ev ) );

        {
            boost::system::error_code bc( ev, bt );

            BOOST_TEST_EQ( bc.value(), ev );
            BOOST_TEST_EQ( &bc.category(), &bt );

            std::error_code sc( bc );

            BOOST_TEST_EQ( sc.value(), ev );
            BOOST_TEST_EQ( &sc.category(), &st );
        }

        {
            boost::system::error_condition bn = bt.default_error_condition( ev );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }
    }
}

class user_category_impl: public boost::system::error_category
{
public:

    virtual const char * name() const BOOST_NOEXCEPT
    {
        return "user";
    }

    virtual std::string message( int ev ) const
    {
        char buffer[ 256 ];
        sprintf( buffer, "user message %d", ev );

        return buffer;
    }

    virtual boost::system::error_condition default_error_condition( int ev ) const BOOST_NOEXCEPT
    {
        if( ev == 4 )
        {
            return boost::system::error_condition( EMFILE, boost::system::generic_category() );
        }
        else if( ev == 5 )
        {
            return boost::system::error_condition( EACCES, boost::system::generic_category() );
        }
        else
        {
            return boost::system::error_condition( ev, *this );
        }
    }

    virtual bool equivalent( int code, const boost::system::error_condition & condition ) const BOOST_NOEXCEPT
    {
        if( code == 4 && condition == make_error_condition( boost::system::errc::too_many_files_open_in_system ) )
        {
            return true;
        }

        if( code == 4 && condition == make_error_condition( boost::system::errc::too_many_files_open ) )
        {
            return true;
        }

        return default_error_condition( code ) == condition;
    }

    // virtual bool equivalent( const error_code & code, int condition ) const BOOST_NOEXCEPT;
};

boost::system::error_category const & user_category()
{
    static user_category_impl cat_;
    return cat_;
}

static void test_user_category()
{
    boost::system::error_category const & bt = user_category();
    std::error_category const & st = bt;

    BOOST_TEST_CSTR_EQ( bt.name(), st.name() );

    {
        int ev = 5;
        BOOST_TEST_EQ( bt.message( ev ), st.message( ev ) );

        {
            boost::system::error_code bc( ev, bt );

            BOOST_TEST_EQ( bc.value(), ev );
            BOOST_TEST_EQ( &bc.category(), &bt );

            std::error_code sc( bc );

            BOOST_TEST_EQ( sc.value(), ev );
            BOOST_TEST_EQ( &sc.category(), &st );
        }

        {
            boost::system::error_condition bn = bt.default_error_condition( ev );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }
    }

    {
        int ev = 4;
        BOOST_TEST_EQ( bt.message( ev ), st.message( ev ) );

        {
            boost::system::error_code bc( ev, bt );

            BOOST_TEST_EQ( bc.value(), ev );
            BOOST_TEST_EQ( &bc.category(), &bt );

            std::error_code sc( bc );

            BOOST_TEST_EQ( sc.value(), ev );
            BOOST_TEST_EQ( &sc.category(), &st );
        }

        {
            boost::system::error_condition bn = bt.default_error_condition( ev );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }

        {
            boost::system::error_condition bn = make_error_condition( boost::system::errc::too_many_files_open_in_system );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }

        {
            boost::system::error_condition bn = make_error_condition( boost::system::errc::too_many_files_open );
            BOOST_TEST( bt.equivalent( ev, bn ) );

            std::error_condition sn( bn );
            BOOST_TEST( st.equivalent( ev, sn ) );
        }
    }
}

int main()
{
    test_generic_category();
    test_system_category();
    test_user_category();

    return boost::report_errors();
}

#endif
