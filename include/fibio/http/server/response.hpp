//
//  response.hpp
//  fibio
//
//  Created by Chen Xu on 14-3-13.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#ifndef fibio_http_server_response_hpp
#define fibio_http_server_response_hpp

#include <string>
#include <boost/interprocess/streams/vectorstream.hpp>
#include <fibio/http/common/response.hpp>

namespace fibio { namespace http {
    struct server_response : common::response {
        server_response()=default;

        server_response(const server_response &other)
        : common::response(other)
        {}

        server_response &operator=(const server_response &other) {
            common::response::operator=(other);
            return *this;
        }
        
        void clear();
        
        size_t get_content_length() const;
        
        void set_content_type(const std::string &);
        
        const std::string &get_body() const;
        
        std::ostream &body_stream();
        
        template<typename T>
        void set_body(const T &t, const std::string &content_type=common::content_type<T>::name) {
            set_content_type(content_type);
            body_stream() << t;
        }
        
        bool write_header(std::ostream &os);
        bool write(std::ostream &os);
        
        boost::interprocess::basic_ovectorstream<std::string> raw_body_stream_;
    };
}}  // End of namespace fibio::http

#endif
