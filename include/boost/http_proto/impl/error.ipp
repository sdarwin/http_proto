//
// Copyright (c) 2021 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_IMPL_ERROR_IPP
#define BOOST_HTTP_PROTO_IMPL_ERROR_IPP

#include <boost/http_proto/error.hpp>
#include <boost/url/grammar/error.hpp>
#include <boost/assert.hpp>
#include <type_traits>
#include <cstring>

namespace boost {
namespace http_proto {

namespace detail {

const char*
error_cat_type::
name() const noexcept
{
    return "boost.http.proto";
}

std::string
error_cat_type::
message(int code) const
{
    return message(code, nullptr, 0);
}

char const*
error_cat_type::
message(
    int code,
    char*,
    std::size_t) const noexcept
{
    switch(static_cast<error>(code))
    {
    case error::expect_100_continue: return "expect continue";
    case error::end_of_message: return "end of message";
    case error::end_of_stream: return "end of stream";
    case error::in_place_overflow: return "in place overflow";
    case error::need_data: return "need data";

    case error::bad_connection: return "bad Connection";
    case error::bad_content_length: return "bad Content-Length";
    case error::bad_expect: return "bad Expect";
    case error::bad_field_name: return "bad field name";
    case error::bad_field_value: return "bad field value";
    case error::bad_line_ending: return "bad line ending";
    case error::bad_list: return "bad list";
    case error::bad_method: return "bad method";
    case error::bad_number: return "bad number";
    case error::bad_payload: return "bad payload";
    case error::bad_version: return "bad version";
    case error::bad_reason: return "bad reason-phrase";
    case error::bad_request_target: return "bad request-target";
    case error::bad_status_code: return "bad status-code";
    case error::bad_status_line: return "bad status-line";
    case error::bad_transfer_encoding: return "bad Transfer-Encoding";
    case error::bad_upgrade: return "bad Upgrade";

    case error::body_too_large: return "body too large";
    case error::headers_limit: return "headers limit";
    case error::start_line_limit: return "start line limit";
    case error::field_size_limit: return "field size limit";
    case error::fields_limit: return "fields limit";
    case error::incomplete: return "incomplete";

    case error::numeric_overflow: return "numeric overflow";
    case error::multiple_content_length: return "multiple Content-Length";
    case error::buffer_overflow: return "buffer overflow";
    default:
        return "unknown";
    }
}

//-----------------------------------------------

const char*
condition_cat_type::
name() const noexcept
{
    return "boost.http.proto";
}

std::string
condition_cat_type::
message(int code) const
{
    return message(code, nullptr, 0);
}

char const*
condition_cat_type::
message(
    int code,
    char*,
    std::size_t) const noexcept
{
    switch(static_cast<condition>(code))
    {
    default:
    case condition::need_more_input: return "need more input";
    }
}

bool
condition_cat_type::
equivalent(
    system::error_code const& ec,
    int code) const noexcept
{
    switch(static_cast<condition>(code))
    {
    case condition::need_more_input:
        if( ec == urls::grammar::error::need_more ||
            ec == error::need_data)
            return true;
        break;

    default:
        break;
    }
    return
        *this == ec.category() &&
        ec.value() == code;
}

} // detail

} // http_proto
} // boost

#endif
