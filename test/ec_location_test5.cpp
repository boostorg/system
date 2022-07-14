// Copyright 2021, 2022 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/system.hpp>
#include <boost/core/lightweight_test.hpp>
#include <cerrno>

#if defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L && defined(BOOST_GCC)

struct get_std_source_location_impl_tag {};
template< class T >
struct get_std_source_location_impl_t
{
    friend auto get_std_source_location_impl( get_std_source_location_impl_tag ) { return T(); }
};
template struct get_std_source_location_impl_t<std::source_location::__impl>;
auto get_std_source_location_impl( get_std_source_location_impl_tag );
using std_source_location_impl = decltype( get_std_source_location_impl( get_std_source_location_impl_tag() ) );

static_assert( static_cast< const std_source_location_impl* >( __builtin_source_location() )->_M_line == __LINE__ );

static_assert( std::is_layout_compatible_v< boost::source_location, std_source_location_impl > );

#elif defined(__cpp_lib_source_location) && __cpp_lib_source_location >= 201907L && defined(BOOST_CLANG)

static_assert( __builtin_source_location()->_M_line == __LINE__ );

static_assert( std::is_layout_compatible_v< boost::source_location,
    std::remove_cvref_t< decltype( *__builtin_source_location() ) > > );

#endif

int main()
{
    int const val = ENOENT;
    boost::system::error_category const & cat = boost::system::generic_category();

    {
        BOOST_STATIC_CONSTEXPR boost::source_location loc = BOOST_CURRENT_LOCATION;

        boost::system::error_code ec( val, cat, BOOST_SYSTEM_CURRENT_LOCATION_PTR );

        BOOST_TEST_EQ( ec.value(), val );
        BOOST_TEST_EQ( &ec.category(), &cat );

        BOOST_TEST( ec.failed() );

        BOOST_TEST( ec.has_location() );
        BOOST_TEST_EQ( ec.location().file_name(), loc.file_name() );
        BOOST_TEST_EQ( ec.location().function_name(), loc.function_name() );
        BOOST_TEST_EQ( ec.location().line(), loc.line() + 2 );
    }

    return boost::report_errors();
}
