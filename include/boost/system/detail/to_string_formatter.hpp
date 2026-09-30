#ifndef BOOST_SYSTEM_DETAIL_TO_STRING_FORMATTER_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_TO_STRING_FORMATTER_HPP_INCLUDED

// Copyright 2026 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX20_HDR_FORMAT)

#include <format>
#include <string_view>

namespace boost
{
namespace system
{
namespace detail
{

template<class T> class to_string_formatter
{
private:

    std::formatter<std::string_view, char> fmt_;

public:

    constexpr auto parse( std::format_parse_context& ctx )
    {
        return fmt_.parse( ctx );
    }

    auto format( T const& t, std::format_context& ctx ) const
    {
        return fmt_.format( t.to_string(), ctx );
    }
};

} // namespace detail
} // namespace system
} // namespace boost

#endif

#endif // #ifndef BOOST_SYSTEM_DETAIL_TO_STRING_FORMATTER_HPP_INCLUDED
