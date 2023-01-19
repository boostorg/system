#ifndef BOOST_SYSTEM_DETAIL_MUTEX_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_MUTEX_HPP_INCLUDED

// Copyright 2023 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt)

#include <boost/config.hpp>

#if defined(BOOST_SYSTEM_DISABLE_THREADS)

namespace boost
{
namespace system
{
namespace detail
{

struct mutex
{
    void lock()
    {
    }

    void unlock()
    {
    }
};

} // namespace detail
} // namespace system
} // namespace boost

#else

#include <mutex>

namespace boost
{
namespace system
{
namespace detail
{

using std::mutex;

} // namespace detail
} // namespace system
} // namespace boost

#endif

namespace boost
{
namespace system
{
namespace detail
{

template<class Mtx> class lock_guard
{
private:

    Mtx& mtx_;

private:

    lock_guard( lock_guard const& );
    lock_guard& operator=( lock_guard const& );

public:

    explicit lock_guard( Mtx& mtx ): mtx_( mtx )
    {
        mtx_.lock();
    }

    ~lock_guard()
    {
        mtx_.unlock();
    }
};

} // namespace detail
} // namespace system
} // namespace boost

#endif // #ifndef BOOST_SYSTEM_DETAIL_MUTEX_HPP_INCLUDED
