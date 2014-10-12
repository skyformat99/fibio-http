//
//  request.hpp
//  fibio
//
//  Created by Chen Xu on 14-3-13.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#ifndef fibio_http_server_request_hpp
#define fibio_http_server_request_hpp

#include <memory>
#include <string>
#include <boost/iostreams/restrict.hpp>
#include <fibio/http/common/request.hpp>

namespace fibio { namespace http {
    struct server_request : common::request {
        void clear();
        
        bool accept_compressed() const;
        
        bool read(std::istream &is);
        
        inline bool has_body() const {
            return content_length>0 && body_stream_.get();
        }
        
        inline std::istream &body_stream() {
            // TODO: Throw if body stream is not setup
            return *(body_stream_.get());
        }
        
        // Consume and discard body
        void drop_body();
        
        std::unique_ptr<boost::iostreams::restriction<std::istream>> restriction_;
        std::unique_ptr<std::istream> body_stream_;
    };

    inline std::istream &operator>>(std::istream &is, server_request &v) {
        v.read(is);
        return is;
    }
}}  // End of namespace fibio::http

#endif
