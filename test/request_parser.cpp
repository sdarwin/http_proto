//
// Copyright (c) 2019 Vinnie Falco (vinnie.falco@gmail.com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/http_proto
//

// Test that header file is self-contained.
#include <boost/http_proto/request_parser.hpp>

#include <boost/http_proto/context.hpp>
#include <algorithm>

#include "test_suite.hpp"

namespace boost {
namespace http_proto {

namespace net {
namespace error {
static int eof = 1;
} // error
} // net

class request_parser_test
{
public:
    context ctx_;

    void
    check(
        method m,
        string_view t,
        int v,
        string_view const s)
    {
        auto const f =
            [&](request_parser const& p)
        {
            auto const req = p.header();
            BOOST_TEST(req.method() == m);
            BOOST_TEST(req.method_str() ==
                to_string(m));
            BOOST_TEST(req.target() == t);
            BOOST_TEST(req.version() == v);
        };

        // single buffer
        {
            error_code ec;
            request_parser p(ctx_);
            auto const b = p.prepare();
            auto const n = (std::min)(
                b.second, s.size());
            BOOST_TEST(n == s.size());
            std::memcpy(
                b.first, s.data(), n);
            p.commit(n);
            p.parse_header(ec);
            BOOST_TEST(! ec);
            //BOOST_TEST(p.is_done());
            if(! ec)
                f(p);
        }

        // two buffers
        for(std::size_t i = 1;
            i < s.size(); ++i)
        {
            error_code ec;
            request_parser p(ctx_);
            // first buffer
            auto b = p.prepare();
            auto n = (std::min)(
                b.second, i);
            BOOST_TEST(n == i);
            std::memcpy(
                b.first, s.data(), n);
            p.commit(n);
            p.parse_header(ec);
            BOOST_TEST(! ec);
            if(ec)
                continue;
            // second buffer
            b = p.prepare();
            n = (std::min)(
                b.second, s.size());
            BOOST_TEST(n == s.size());
            std::memcpy(
                b.first, s.data() + i, n);
            p.commit(n);
            p.parse_header(ec);
            BOOST_TEST(! ec);
            if(ec)
                continue;
            //BOOST_TEST(p.is_done());
            f(p);
        }
    }

    void
    testParse()
    {
        check(method::get, "/", 11,
            "GET / HTTP/1.1\r\n"
            "Connection: close\r\n"
            "\r\n");
    }

    struct socket
    {
    };

    template<
        class ReadStream>
    void
    read_more(
        ReadStream&,
        basic_parser&,
        error_code&)
    {
    }

    /*
        Accumulated wisdom

        * Committing bytes is orthogonal to parsing

        * Caller needs to know if more committed bytes are needed

        * All parsing is possibly partial
    */
    void
    sandbox()
    {
        //
        // Read header+body inline
        //
        {
            socket sock;
            error_code ec;
            request_parser p(ctx_);

            // read the header
            for(;;)
            {
                p.parse_header(ec);
                if(! ec)
                    break;
                if(ec != error::need_more)
                    return; // failed
                read_more(sock, p, ec);
                if(! ec)
                    continue;
                if(ec != error::eof)
                    return; // failed
                p.commit_eof();
            }

            // access the header
            request_view req = p.header();

            // read the body inline
            for(;;)
            {
                p.parse_body(ec);
                if(! ec)
                    break;
                if(ec != error::need_more)
                    return; // failed
                read_more(sock, p, ec);
                if(! ec)
                    continue;
                if(ec != error::eof)
                    return; // failed
                p.commit_eof();
            }

            // access the body
            auto body = p.body();

            // prepare for another parse
            p.reset();
        }
    }

    void
    run()
    {
        sandbox();
    }
};

TEST_SUITE(request_parser_test, "boost.http_proto.request_parser");

} // http_proto
} // boost

