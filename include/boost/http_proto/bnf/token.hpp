//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

#ifndef BOOST_HTTP_PROTO_BNF_TOKEN_HPP
#define BOOST_HTTP_PROTO_BNF_TOKEN_HPP

#include <boost/http_proto/detail/config.hpp>
#include <boost/http_proto/error.hpp>

namespace boost {
namespace http_proto {
namespace bnf {

/** BNF for token

    @par BNF
    @code
    token             = 1*tchar
    @endcode
*/
struct token
{
    using value_type = string_view;

    BOOST_HTTP_PROTO_DECL
    static
    char const*
    parse_element(
        value_type& result,
        char const* const start,
        char const* const end,
        error_code& ec);
};

} // bnf
} // http_proto
} // boost

#endif
