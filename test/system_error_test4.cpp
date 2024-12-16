// Copyright 2021, 2022 Peter Dimov
// Distributed under the Boost Software License, Version 1.0
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/system/system_error.hpp>
#include <boost/core/lightweight_test.hpp>
#include <cerrno>

namespace sys = boost::system;

int main()
{
    try {
        sys::error_code ec( 5, sys::generic_category() );
        throw sys::system_error( ec );
    } catch (const std::system_error& err) {
        // fine
    }

    return boost::report_errors();
}
