#ifndef BOOST_SYSTEM_DETAIL_INVOKE_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_INVOKE_HPP_INCLUDED

// Copyright 2024, 2025 Peter Dimov
// Distributed under the Boost Software License, Version 1.0
// http://www.boost.org/LICENSE_1_0.txt

#include <functional>
#include <type_traits>

#define BOOST_SYSTEM_DETAIL_RETURNS(...) noexcept(noexcept(__VA_ARGS__)) -> decltype(__VA_ARGS__) { return __VA_ARGS__; }

namespace boost
{
namespace system
{
namespace detail
{

// invoke

template<class F, class... A>
constexpr auto invoke( F&& f, A&&... a )
BOOST_SYSTEM_DETAIL_RETURNS( std::forward<F>(f)(std::forward<A>(a)...) )

template<class M, class T, class... A>
constexpr auto invoke( M T::* pm, A&&... a )
BOOST_SYSTEM_DETAIL_RETURNS( std::mem_fn(pm)(std::forward<A>(a)...) )

// invoke_result_t

template<class F, class... A> using invoke_result_t = decltype( detail::invoke( std::declval<F>(), std::declval<A>()... ) );

} // namespace detail
} // namespace system
} // namespace boost

#endif // #ifndef BOOST_SYSTEM_DETAIL_INVOKE_HPP_INCLUDED
