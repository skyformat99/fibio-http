//
//  common.cpp
//  fibio
//
//  Created by Chen Xu on 14-3-10.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#include <string>
#include <iostream>
#include "../../http-parser/http_parser.h"
#include <boost/lexical_cast.hpp>
#include <fibio/http/common/common_types.hpp>
#include <fibio/http/common/request.hpp>
#include <fibio/http/common/response.hpp>

namespace fibio { namespace http { namespace common {
    namespace detail {
        const std::map<http_version, std::string> http_version_name_map={
            {http_version::HTTP_0_9, "HTTP/0.9"},
            {http_version::HTTP_1_0, "HTTP/1.0"},
            {http_version::HTTP_1_1, "HTTP/1.1"},
        };
        
        const std::map<std::string, http_version, iless> name_http_version_map={
            {"HTTP/0.9", http_version::HTTP_0_9},
            {"HTTP/1.0", http_version::HTTP_1_0},
            {"HTTP/1.1", http_version::HTTP_1_1},
        };
        
        const std::map<http_method, std::string> method_name_map={
            {http_method::DELETE, "DELETE"},
            {http_method::GET, "GET"},
            {http_method::HEAD, "HEAD"},
            {http_method::POST, "POST"},
            {http_method::PUT, "PUT"},
            /* pathological */
            {http_method::CONNECT, "CONNECT"},
            {http_method::OPTIONS, "OPTIONS"},
            {http_method::TRACE, "TRACE"},
            /* webdav */
            {http_method::COPY, "COPY"},
            {http_method::LOCK, "LOCK"},
            {http_method::MKCOL, "MKCOL"},
            {http_method::MOVE, "MOVE"},
            {http_method::PROPFIND, "PROPFIND"},
            {http_method::PROPPATCH, "PROPPATCH"},
            {http_method::SEARCH, "SEARCH"},
            {http_method::UNLOCK, "UNLOCK"},
            /* subversion */
            {http_method::REPORT, "REPORT"},
            {http_method::MKACTIVITY, "MKACTIVITY"},
            {http_method::CHECKOUT, "CHECKOUT"},
            {http_method::MERGE, "MERGE"},
            /* upnp */
            {http_method::MSEARCH, "MSEARCH"},
            {http_method::NOTIFY, "NOTIFY"},
            {http_method::SUBSCRIBE, "SUBSCRIBE"},
            {http_method::UNSUBSCRIBE, "UNSUBSCRIBE"},
            /* RFC-5789 */
            {http_method::PATCH, "PATCH"},
            {http_method::PURGE, "PURGE"},
        };

        const std::map<std::string, http_method, iless> name_method_map={
            {"DELETE",  http_method::DELETE},
            {"GET",     http_method::GET},
            {"HEAD",    http_method::HEAD},
            {"POST",    http_method::POST},
            {"PUT",     http_method::PUT},
            /* pathological */
            {"CONNECT", http_method::CONNECT},
            {"OPTIONS", http_method::OPTIONS},
            {"TRACE",   http_method::TRACE},
            /* webdav */
            {"COPY",    http_method::COPY},
            {"LOCK",    http_method::LOCK},
            {"MKCOL",   http_method::MKCOL},
            {"MOVE",    http_method::MOVE},
            {"PROPFIND",http_method::PROPFIND},
            {"PROPPATCH", http_method::PROPPATCH},
            {"SEARCH",  http_method::SEARCH},
            {"UNLOCK",  http_method::UNLOCK},
            /* subversion */
            {"REPORT",  http_method::REPORT},
            {"MKACTIVITY",  http_method::MKACTIVITY},
            {"CHECKOUT",    http_method::CHECKOUT},
            {"MERGE",   http_method::MERGE},
            /* upnp */
            {"MSEARCH", http_method::MSEARCH},
            {"NOTIFY",  http_method::NOTIFY},
            {"SUBSCRIBE",   http_method::SUBSCRIBE},
            {"UNSUBSCRIBE", http_method::UNSUBSCRIBE},
            /* RFC-5789 */
            {"PATCH",   http_method::PATCH},
            {"PURGE",   http_method::PURGE},
        };
        
        const std::map<http_status_code, std::string> status_msg_map={
            {http_status_code::CONTINUE                        , "Continue"},
            {http_status_code::SWITCHING_PROTOCOLS             , "Switching Protocols"},
            {http_status_code::OK                              , "OK"},
            {http_status_code::CREATED                         , "Created"},
            {http_status_code::ACCEPTED                        , "Accepted"},
            {http_status_code::NON_AUTHORITATIVE_INFORMATION   , "Non-Authoritative Information"},
            {http_status_code::NO_CONTENT                      , "No Content"},
            {http_status_code::RESET_CONTENT                   , "Reset Content"},
            {http_status_code::PARTIAL_CONTENT                 , "Partial Content"},
            {http_status_code::MULTIPLE_CHOICES                , "Multiple Choices"},
            {http_status_code::MOVED_PERMANENTLY               , "Moved Permanently"},
            {http_status_code::FOUND                           , "Found"},
            {http_status_code::SEE_OTHER                       , "See Other"},
            {http_status_code::NOT_MODIFIED                    , "Not Modified"},
            {http_status_code::USE_PROXY                       , "Use Proxy"},
            //http_status_code::UNUSED                         , "(Unused)"},
            {http_status_code::TEMPORARY_REDIRECT              , "Temporary Redirect"},
            {http_status_code::BAD_REQUEST                     , "Bad Request"},
            {http_status_code::UNAUTHORIZED                    , "Unauthorized"},
            {http_status_code::PAYMENT_REQUIRED                , "Payment Required"},
            {http_status_code::FORBIDDEN                       , "Forbidden"},
            {http_status_code::NOT_FOUND                       , "Not Found"},
            {http_status_code::METHOD_NOT_ALLOWED              , "Method Not Allowed"},
            {http_status_code::NOT_ACCEPTABLE                  , "Not Acceptable"},
            {http_status_code::PROXY_AUTHENTICATION_REQUIRED   , "Proxy Authentication Required"},
            {http_status_code::REQUEST_TIMEOUT                 , "Request Timeout"},
            {http_status_code::CONFLICT                        , "Conflict"},
            {http_status_code::GONE                            , "Gone"},
            {http_status_code::LENGTH_REQUIRED                 , "Length Required"},
            {http_status_code::PRECONDITION_FAILED             , "Precondition Failed"},
            {http_status_code::REQUEST_ENTITY_TOO_LARGE        , "Request Entity Too Large"},
            {http_status_code::REQUEST_URI_TOO_LONG            , "Request-URI Too Long"},
            {http_status_code::UNSUPPORTED_MEDIA_TYPE          , "Unsupported Media Type"},
            {http_status_code::REQUESTED_RANGE_NOT_SATISFIABLE , "Requested Range Not Satisfiable"},
            {http_status_code::EXPECTATION_FAILED              , "Expectation Failed"},
            {http_status_code::UPGRADE_REQUIRED                , "Upgrade Required"},
            {http_status_code::PRECONDITION_REQUIRED           , "Precondition Required"},
            {http_status_code::TOO_MANY_REQUESTS               , "Too Many Requests"},
            {http_status_code::REQUEST_HEADER_FIELDS_TOO_LARGE , "Request Header Fields Too Large"},
            {http_status_code::INTERNAL_SERVER_ERROR           , "Internal Server Error"},
            {http_status_code::NOT_IMPLEMENTED                 , "Not Implemented"},
            {http_status_code::BAD_GATEWAY                     , "Bad Gateway"},
            {http_status_code::SERVICE_UNAVAILABLE             , "Service Unavailable"},
            {http_status_code::GATEWAY_TIMEOUT                 , "Gateway Timeout"},
            {http_status_code::HTTP_VERSION_NOT_SUPPORTED      , "HTTP Version Not Supported"},
        };
        
        struct request_parser {
            typedef request_parser parser_type;
            request_parser(request &req)
            : req_(req)
            {}
            
            bool parse(std::istream &is);
            
            int on_message_begin() {
                req_.clear();
                state_=start;
                return 0;
            }
            
            int on_url(const char *at, size_t length) {
                if(state_==url)
                    req_.url.append(at, length);
                else {
                    req_.url.reserve(1024);
                    req_.url.assign(at, length);
                }
                state_=url;
                return 0;
            }
            
            int on_status(const char *at, size_t length) {
                // request doesn't have status line
                return 0;
            }
            
            int on_header_field(const char *at, size_t length) {
                if (state_==field) {
                    current_field_.append(at, length);
                } else {
                    if (state_==value) {
                        // One header line finished
                        req_.headers.insert(std::make_pair(current_field_, current_value_));
                    }
                    current_field_.reserve(256);
                    current_field_.assign(at, length);
                }
                state_=field;
                return 0;
            }
            
            int on_header_value(const char *at, size_t length) {
                if (state_==value)
                    current_value_.append(at, length);
                else {
                    current_value_.reserve(256);
                    current_value_.assign(at, length);
                }
                state_=value;
                return 0;
            }
            
            int on_headers_complete() {
                // Finish last header
                if (!current_field_.empty() && !current_value_.empty()) {
                    req_.headers.insert(std::make_pair(current_field_, current_value_));
                }
                return 1;
            }
            
            int on_body(const char *at, size_t length) {
                return 0;
            }
            
            int on_message_complete() {
                // Don't parse body
                state_=header_complete;
                
                // Setup keep_alive flag
                req_.keep_alive=(http_should_keep_alive(&parser_)!=0);
                
                // Set content length
                req_.content_length=parser_.content_length;
                if (req_.content_length==ULONG_MAX) req_.content_length=0;
                
                // Set HTTP version
                if (parser_.http_major==0 && parser_.http_minor==9) {
                    req_.version=http_version::HTTP_0_9;
                } else if (parser_.http_major==1 && parser_.http_minor==0) {
                    req_.version=http_version::HTTP_1_0;
                } else if (parser_.http_major==1 && parser_.http_minor==1) {
                    req_.version=http_version::HTTP_1_1;
                } else {
                    req_.version=http_version::INVALID;
                }
                
                // Set HTTP method
                req_.method = static_cast<http_method>(parser_.method);
                
                return 0;
            }
            
            enum parser_state {
                none,
                start,
                url,
                field,
                value,
                header_complete,
                body,
                end
            };
            
            http_parser parser_;
            request &req_;
            parser_state state_;
            std::string current_field_;
            std::string current_value_;
        };
        
        namespace request {
            static int on_message_begin(http_parser*p) {
                return reinterpret_cast<request_parser *>(p->data)->on_message_begin();
            }
            static int on_url(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<request_parser *>(p->data)->on_url(at, length);
            }
            static int on_status(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<request_parser *>(p->data)->on_status(at, length);
            }
            static int on_header_field(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<request_parser *>(p->data)->on_header_field(at, length);
            }
            static int on_header_value(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<request_parser *>(p->data)->on_header_value(at, length);
            }
            static int on_headers_complete(http_parser*p) {
                return reinterpret_cast<request_parser *>(p->data)->on_headers_complete();
            }
            static int on_body(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<request_parser *>(p->data)->on_body(at, length);
            }
            static int on_message_complete(http_parser*p) {
                return reinterpret_cast<request_parser *>(p->data)->on_message_complete();
            }
            
            static constexpr http_parser_settings settings={
                &on_message_begin,
                &on_url,
                &on_status,
                &on_header_field,
                &on_header_value,
                &on_headers_complete,
                &on_body,
                &on_message_complete,
            };
        }   // End of namespace fibio::http::common::detail::request
        
        bool request_parser::parse(std::istream &is) {
            http_parser_init(&parser_, HTTP_REQUEST);
            parser_.data=reinterpret_cast<void*>(this);
            state_=none;

            constexpr int buf_size=1024;
            char buf[buf_size];
            int recved=0;
            int nparsed=0;
            while (!is.eof()) {
                // Read some data
                recved = is.readsome(buf, buf_size);
                if (recved<=0) {
                    // Connection closed
                    return true;
                }
                nparsed=http_parser_execute(&parser_, &request::settings, buf, recved);
                if (state_==header_complete) {
                    // Parse error
                    if (nparsed>=0) {
                        // Move read pointer back to where parser consumed
                        std::streamsize off=std::streamsize(nparsed);
                        off-=recved;
                        is.seekg(off, std::ios_base::cur);
                    }
                    return true;
                } else if (nparsed!=recved) {
                    return false;
                }
            }
            return true;
        }
        
        struct response_parser {
            typedef response_parser parser_type;
            response_parser(response &resp)
            : resp_(resp)
            {}
            
            bool parse(std::istream &is);
            
            int on_message_begin() {
                resp_.clear();
                state_=start;
                return 0;
            }
            
            int on_url(const char *at, size_t length) {
                return 0;
            }
            
            int on_status(const char *at, size_t length) {
                if(state_==status)
                    resp_.status_message.append(at, length);
                else {
                    resp_.status_message.reserve(100);
                    resp_.status_message.assign(at, length);
                }
                state_=status;
                return 0;
            }
            
            int on_header_field(const char *at, size_t length) {
                if (state_==field) {
                    current_field_.append(at, length);
                } else {
                    if (state_==value) {
                        // One header line finished
                        resp_.headers.insert(std::make_pair(current_field_, current_value_));
                    }
                    current_field_.reserve(256);
                    current_field_.assign(at, length);
                }
                state_=field;
                return 0;
            }
            
            int on_header_value(const char *at, size_t length) {
                if (state_==value)
                    current_value_.append(at, length);
                else {
                    current_value_.reserve(256);
                    current_value_.assign(at, length);
                }
                state_=value;
                return 0;
            }
            
            int on_headers_complete() {
                // Finish last header
                if (!current_field_.empty() && !current_value_.empty()) {
                    resp_.headers.insert(std::make_pair(current_field_, current_value_));
                }
                return 1;
            }
            
            int on_body(const char *at, size_t length) {
                return 0;
            }
            
            int on_message_complete() {
                // Don't parse body
                state_=header_complete;
                
                // Setup keep_alive flag
                resp_.keep_alive=(http_should_keep_alive(&parser_)!=0);
                
                // Set content length
                resp_.content_length=parser_.content_length;
                if (resp_.content_length==ULONG_MAX) resp_.content_length=0;
                
                // Set HTTP version
                if (parser_.http_major==0 && parser_.http_minor==9) {
                    resp_.version=http_version::HTTP_0_9;
                } else if (parser_.http_major==1 && parser_.http_minor==0) {
                    resp_.version=http_version::HTTP_1_0;
                } else if (parser_.http_major==1 && parser_.http_minor==1) {
                    resp_.version=http_version::HTTP_1_1;
                } else {
                    resp_.version=http_version::INVALID;
                }
                
                // Set HTTP method
                resp_.status_code = static_cast<http_status_code>(parser_.status_code);
                
                return 0;
            }
            
            enum parser_state {
                none,
                start,
                status,
                field,
                value,
                header_complete,
                body,
                end
            };
            
            http_parser parser_;
            response &resp_;
            parser_state state_;
            std::string current_field_;
            std::string current_value_;
        };
        
        namespace response {
            static int on_message_begin(http_parser*p) {
                return reinterpret_cast<response_parser *>(p->data)->on_message_begin();
            }
            static int on_url(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<response_parser *>(p->data)->on_url(at, length);
            }
            static int on_status(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<response_parser *>(p->data)->on_status(at, length);
            }
            static int on_header_field(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<response_parser *>(p->data)->on_header_field(at, length);
            }
            static int on_header_value(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<response_parser *>(p->data)->on_header_value(at, length);
            }
            static int on_headers_complete(http_parser*p) {
                return reinterpret_cast<response_parser *>(p->data)->on_headers_complete();
            }
            static int on_body(http_parser*p, const char *at, size_t length) {
                return reinterpret_cast<response_parser *>(p->data)->on_body(at, length);
            }
            static int on_message_complete(http_parser*p) {
                return reinterpret_cast<response_parser *>(p->data)->on_message_complete();
            }
            
            static constexpr http_parser_settings settings={
                &on_message_begin,
                &on_url,
                &on_status,
                &on_header_field,
                &on_header_value,
                &on_headers_complete,
                &on_body,
                &on_message_complete,
            };
        }   // End of namespace fibio::http::common::detail::response
        
        bool response_parser::parse(std::istream &is) {
            http_parser_init(&parser_, HTTP_RESPONSE);
            parser_.data=reinterpret_cast<void*>(this);
            state_=none;
            
            constexpr int buf_size=1024;
            char buf[buf_size];
            int recved=0;
            int nparsed=0;
            while (!is.eof()) {
                // Read some data
                recved = is.readsome(buf, buf_size);
                if (recved<=0) {
                    // Connection closed
                    return true;
                }
                nparsed=http_parser_execute(&parser_, &response::settings, buf, recved);
                if (nparsed!=recved) {
                    // Parse error
                    if (nparsed>=0) {
                        // Move read pointer back to where parser consumed
                        std::streamsize off=std::streamsize(nparsed);
                        off-=recved;
                        is.seekg(off, std::ios_base::cur);
                    }
                    if (state_==header_complete) {
                        return true;
                    }
                    return false;
                }
            }
            return true;
        }
    }   // End of namespace fibio::http::common::detail
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // request
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void request::clear() {
        method=http_method::INVALID;
        url.clear();
        version=http_version::INVALID;
        headers.clear();
        content_length=0;
        keep_alive=false;
    }
    
    bool request::read(std::istream &is) {
        detail::request_parser parser(*this);
        return parser.parse(is);
    }
    
    bool request::write(std::ostream &os) {
        // Some validation
        if (method==http_method::INVALID) return false;
        if (url.empty()) return false;
        if (version==http_version::INVALID) return false;
        
        // METHOD " " URL " " HTTP_VER "\r\n"
        auto m=detail::method_name_map.find(method);
        if (m==detail::method_name_map.end()) return false;
        os.write(&(m->second[0]), m->second.size());
        os.write(" ", 1);
        os.write(&(url[0]), url.size());
        os.write(" ", 1);
        auto v=detail::http_version_name_map.find(version);
        if (v==detail::http_version_name_map.end()) return false;
        os.write(&(v->second[0]), v->second.size());
        os.write("\r\n", 2);
        
        // Write headers
        for (auto &p: headers) {
            os.write(&(p.first[0]), p.first.size());
            os.write(": ", 2);
            os.write(&(p.second[0]), p.second.size());
            os.write("\r\n", 2);
        }
        // End of header
        os.write("\r\n", 2);
        return true;
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    // response
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void response::clear() {
        status_code=http_status_code::INVALID;
        status_message.clear();
        version=http_version::INVALID;
        headers.clear();
        content_length=0;
        keep_alive=false;
    }
    
    bool response::read(std::istream &is) {
        detail::response_parser parser(*this);
        return parser.parse(is);
    }
    
    bool response::write(std::ostream &os) {
        // Some validation
        if (status_code==http_status_code::INVALID) return false;
        //if (status_message.empty()) return false;
        if (version==http_version::INVALID) return false;
        
        // HTTP_VER " " STATUS_CODE URL " "  "\r\n"
        auto v=detail::http_version_name_map.find(version);
        if (v==detail::http_version_name_map.end()) return false;
        os.write(&(v->second[0]), v->second.size());
        os.write(" ", 1);
        
        std::string sc=boost::lexical_cast<std::string>(static_cast<unsigned short>(status_code));
        os.write(&(sc[0]), sc.size());
        os.write(" ", 1);

        auto s=detail::status_msg_map.find(status_code);
        if (s==detail::status_msg_map.end()) return false;
        os.write(&(s->second[0]), s->second.size());
        os.write("\r\n", 2);
        
        // Write headers
        for (auto &p: headers) {
            os.write(&(p.first[0]), p.first.size());
            os.write(": ", 2);
            os.write(&(p.second[0]), p.second.size());
            os.write("\r\n", 2);
        }
        // End of header
        os.write("\r\n", 2);
        return true;
    }
}}} // End of namespace fibio::http::common
