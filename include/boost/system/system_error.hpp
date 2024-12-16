#ifndef BOOST_SYSTEM_SYSTEM_ERROR_HPP
#define BOOST_SYSTEM_SYSTEM_ERROR_HPP

// Copyright Beman Dawes 2006
// Copyright Peter Dimov 2021
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/system/errc.hpp>
#include <boost/system/detail/error_code.hpp>
#include <string>
#include <stdexcept>
#include <system_error>
#include <cassert>

namespace boost
{
namespace system
{

class BOOST_SYMBOL_VISIBLE system_error: public std::system_error
{
public:
    using std::system_error::system_error;

    error_code code() const noexcept
    {
        return std::system_error::code();
    }
};

} // namespace system
} // namespace boost

#endif // BOOST_SYSTEM_SYSTEM_ERROR_HPP
