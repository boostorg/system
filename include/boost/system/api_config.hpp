//  boost/system/api_config.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2003, 2006, 2010

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  See http://www.boost.org/libs/system for documentation.

//--------------------------------------------------------------------------------------//

//  Boost.System calls operating system API functions to implement system error category
//  functions. Usually there is no question as to which API is to be used.
//
//  In the case of MinGW or Cygwin/MinGW, however, both POSIX and Windows API's are
//  available. Chaos ensues if other code thinks one is in use when Boost.System was
//  actually built with the other. This header centralizes the API choice and prevents
//  user definition of API macros, thus elminating the possibility of mismatches and the
//  need to test configurations with little or no practical value.
//

//--------------------------------------------------------------------------------------//

#ifndef BOOST_SYSTEM_API_CONFIG_HPP                  
#define BOOST_SYSTEM_API_CONFIG_HPP

# if defined(BOOST_POSIX_API) || defined(BOOST_WINDOWS_API)
#   error user defined BOOST_POSIX_API or BOOST_WINDOWS_API not supported
# endif

//  BOOST_POSIX_API or BOOST_WINDOWS_API specify which API to use
//    Cygwin/MinGW does not predefine _WIN32.
//    Standalone MinGW and all other known Windows compilers do predefine _WIN32
//    Compilers that predefine _WIN32 or __MINGW32__ do so for Windows 64-bit builds too.

# if defined(_WIN32) || defined(__CYGWIN__) // Windows default, including MinGW and Cygwin
#   define BOOST_WINDOWS_API
# else
#   define BOOST_POSIX_API 
# endif

# if !defined(BOOST_SYSTEM_NO_DEPRECATION_WARNING) && defined(BOOST_WINDOWS_API) && defined(BOOST_NO_ANSI_APIS) && !defined(BOOST_SYSTEM_USE_UTF8)
#   if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#     pragma message ("Using ASNI strings with UNICODE API is deprecated, please define BOOST_SYSTEM_USE_UTF8 to use UTF8 strings. To disable this warning message, define BOOST_SYSTEM_NO_DEPRECATION_WARNING")
#   elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#     warning "Using ASNI strings with UNICODE API is deprecated, please define BOOST_SYSTEM_USE_UTF8 to use UTF8 strings. To disable this warning message, define BOOST_SYSTEM_NO_DEPRECATION_WARNING"
#   endif
# endif
                                     
#endif  // BOOST_SYSTEM_API_CONFIG_HPP 
