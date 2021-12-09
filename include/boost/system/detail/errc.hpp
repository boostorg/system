#ifndef BOOST_SYSTEM_DETAIL_ERRC_HPP_INCLUDED
#define BOOST_SYSTEM_DETAIL_ERRC_HPP_INCLUDED

// Copyright Beman Dawes 2006, 2007
// Copyright Christoper Kohlhoff 2007
// Copyright Peter Dimov 2017, 2018, 2020
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See library home page at http://www.boost.org/libs/system

#include <boost/system/is_error_condition_enum.hpp>
#include <boost/system/detail/cerrno.hpp>
#include <boost/config.hpp>

namespace boost
{
namespace system
{

#define BOOST_SYSTEM_ENUMERATE_ERRC(F, G) \
    F(success, 0) \
    F(address_family_not_supported, EAFNOSUPPORT) \
    F(address_in_use, EADDRINUSE) \
    F(address_not_available, EADDRNOTAVAIL) \
    F(already_connected, EISCONN) \
    F(argument_list_too_long, E2BIG) \
    F(argument_out_of_domain, EDOM) \
    F(bad_address, EFAULT) \
    F(bad_file_descriptor, EBADF) \
    F(bad_message, EBADMSG) \
    F(broken_pipe, EPIPE) \
    F(connection_aborted, ECONNABORTED) \
    F(connection_already_in_progress, EALREADY) \
    F(connection_refused, ECONNREFUSED) \
    F(connection_reset, ECONNRESET) \
    F(cross_device_link, EXDEV) \
    F(destination_address_required, EDESTADDRREQ) \
    F(device_or_resource_busy, EBUSY) \
    F(directory_not_empty, ENOTEMPTY) \
    F(executable_format_error, ENOEXEC) \
    F(file_exists, EEXIST) \
    F(file_too_large, EFBIG) \
    F(filename_too_long, ENAMETOOLONG) \
    F(function_not_supported, ENOSYS) \
    F(host_unreachable, EHOSTUNREACH) \
    F(identifier_removed, EIDRM) \
    F(illegal_byte_sequence, EILSEQ) \
    F(inappropriate_io_control_operation, ENOTTY) \
    F(interrupted, EINTR) \
    F(invalid_argument, EINVAL) \
    F(invalid_seek, ESPIPE) \
    F(io_error, EIO) \
    F(is_a_directory, EISDIR) \
    F(message_size, EMSGSIZE) \
    F(network_down, ENETDOWN) \
    F(network_reset, ENETRESET) \
    F(network_unreachable, ENETUNREACH) \
    F(no_buffer_space, ENOBUFS) \
    F(no_child_process, ECHILD) \
    F(no_link, ENOLINK) \
    F(no_lock_available, ENOLCK) \
    F(no_message_available, ENODATA) \
    F(no_message, ENOMSG) \
    F(no_protocol_option, ENOPROTOOPT) \
    F(no_space_on_device, ENOSPC) \
    F(no_stream_resources, ENOSR) \
    F(no_such_device_or_address, ENXIO) \
    F(no_such_device, ENODEV) \
    F(no_such_file_or_directory, ENOENT) \
    F(no_such_process, ESRCH) \
    F(not_a_directory, ENOTDIR) \
    F(not_a_socket, ENOTSOCK) \
    F(not_a_stream, ENOSTR) \
    F(not_connected, ENOTCONN) \
    F(not_enough_memory, ENOMEM) \
    F(not_supported, ENOTSUP) \
    F(operation_canceled, ECANCELED) \
    F(operation_in_progress, EINPROGRESS) \
    F(operation_not_permitted, EPERM) \
    F(operation_not_supported, EOPNOTSUPP) \
    F(operation_would_block, EWOULDBLOCK) \
    F(owner_dead, EOWNERDEAD) \
    F(permission_denied, EACCES) \
    F(protocol_error, EPROTO) \
    F(protocol_not_supported, EPROTONOSUPPORT) \
    F(read_only_file_system, EROFS) \
    F(resource_deadlock_would_occur, EDEADLK) \
    F(resource_unavailable_try_again, EAGAIN) \
    F(result_out_of_range, ERANGE) \
    F(state_not_recoverable, ENOTRECOVERABLE) \
    F(stream_timeout, ETIME) \
    F(text_file_busy, ETXTBSY) \
    F(timed_out, ETIMEDOUT) \
    F(too_many_files_open_in_system, ENFILE) \
    F(too_many_files_open, EMFILE) \
    F(too_many_links, EMLINK) \
    F(too_many_symbolic_link_levels, ELOOP) \
    F(value_too_large, EOVERFLOW) \
    G(wrong_protocol_type, EPROTOTYPE)

namespace errc
{

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS) && !defined(BOOST_SYSTEM_ENABLE_DEPRECATED)
enum class errc_t
#else
enum errc_t
#endif
{

#define BOOST_SYSTEM_DEFINE_ERRC(x, y) x = y,
#define BOOST_SYSTEM_DEFINE_ERRC2(x, y) x = y
BOOST_SYSTEM_ENUMERATE_ERRC(BOOST_SYSTEM_DEFINE_ERRC, BOOST_SYSTEM_DEFINE_ERRC2)
#undef BOOST_SYSTEM_DEFINE_ERRC
#undef BOOST_SYSTEM_DEFINE_ERRC2

}; // enum errc_t

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS) && !defined(BOOST_SYSTEM_ENABLE_DEPRECATED)

#define BOOST_SYSTEM_SURFACE_ERRC(x, y) BOOST_CONSTEXPR_OR_CONST errc_t x = errc_t::x;
BOOST_SYSTEM_ENUMERATE_ERRC(BOOST_SYSTEM_SURFACE_ERRC, BOOST_SYSTEM_SURFACE_ERRC)
#undef BOOST_SYSTEM_SURFACE_ERRC

#endif

} // namespace errc

#undef BOOST_SYSTEM_ENUMERATE_ERRC

#ifdef BOOST_SYSTEM_ENABLE_DEPRECATED

namespace posix = errc;
namespace posix_error = errc;

#endif

template<> struct is_error_condition_enum<errc::errc_t>
{
    static const bool value = true;
};

} // namespace system
} // namespace boost

#endif // #ifndef BOOST_SYSTEM_DETAIL_ERRC_HPP_INCLUDED
