
// Copyright 2018 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.

#include <boost/system/error_code.hpp>

using namespace boost::system;

namespace lib1
{

error_code get_system_code()
{
    return error_code( 0, system_category() );
}

error_code get_generic_code()
{
    return error_code( 0, generic_category() );
}

} // namespace lib1
