
// Copyright 2018 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.

#include <boost/system/error_code.hpp>
#include <cerrno>

using namespace boost::system;

static error_code e2( ENOENT, generic_category() );
