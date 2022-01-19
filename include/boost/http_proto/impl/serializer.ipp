//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/CPPAlliance/http_proto
//

#ifndef BOOST_HTTP_PROTO_IMPL_SERIALIZER_IPP
#define BOOST_HTTP_PROTO_IMPL_SERIALIZER_IPP

#include <boost/http_proto/serializer.hpp>

namespace boost {
namespace http_proto {

/*

38 chars:
Content-Length: 18446744073709551615rn
12345678901234567890123456789012345678
         1         2         3       3

Transfer-Encoding: 
*/
serializer::
~serializer()
{
    if(buf_)
        delete[] buf_;
}

serializer::
serializer(
    context& ctx) noexcept
    : ctx_(ctx)
{
    (void)ctx_;
    (void)cap_;
    (void)size_;
}

//------------------------------------------------

void
serializer::
set_header(
    basic_header const&) noexcept
{
}

void
serializer::
set_body(
    void const*,
    std::size_t) noexcept
{
}

void
serializer::
reset() noexcept
{
}

void
serializer::
clear() noexcept
{
}

const_buffer_pair
serializer::
prepare(
    error_code& ec)
{
    ec = {};
    const_buffer_pair p;
    p.data[0] = hs_.data();
    p.size[0] = hs_.size();
    p.data[1] = bs_.data();
    p.size[1] = bs_.size();
    return p;
}

void
serializer::
consume(
    std::size_t) noexcept
{
}

} // http_proto
} // boost

#endif
