//  error_code stub implementation, for compatibility only

//  Copyright Beman Dawes 2002, 2006
//  Copyright Peter Dimov 2018

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

//----------------------------------------------------------------------------//

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_SYSTEM_DYN_LINK)
# define BOOST_SYSTEM_DECL BOOST_SYMBOL_EXPORT
#else
# define BOOST_SYSTEM_DECL
#endif

namespace boost
{

namespace system
{

BOOST_SYSTEM_DECL void dummy_exported_function()
{
}

} // namespace system

} // namespace boost
