//
//  client.hpp
//  fibio
//
//  Created by Chen Xu on 14-3-11.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#ifndef fibio_http_client_client_hpp
#define fibio_http_client_client_hpp

#include <string>
#include <functional>
#include <fibio/stream/iostream.hpp>
#include <fibio/http/client/request.hpp>
#include <fibio/http/client/response.hpp>

namespace fibio { namespace http {
    struct client {
        typedef fibio::http::client_request request;
        typedef fibio::http::client_response response;
        
        client()=default;
        client(const std::string &server, const std::string &port);
        client(const std::string &server, int port);
        
        boost::system::error_code connect(const std::string &server, const std::string &port);
        boost::system::error_code connect(const std::string &server, int port);
        void disconnect();
        
        void set_auto_decompress(bool c);
        bool get_auto_decompress() const;
        
        bool send_request(request &req, response &resp);
        
        std::string server_;
        std::string port_;
        stream::tcp_stream stream_;
        bool auto_decompress_=false;
    };
}}  // End of namespace fibio::http

#endif
