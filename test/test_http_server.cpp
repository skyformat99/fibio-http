//
//  test_http_client.cpp
//  fibio
//
//  Created by Chen Xu on 14-3-12.
//  Copyright (c) 2014 0d0a.com. All rights reserved.
//

#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <boost/asio/basic_waitable_timer.hpp>
#include <fibio/fiber.hpp>
#include <fibio/http/client/client.hpp>
#include <fibio/http/server/server.hpp>
#include <fibio/fiberize.hpp>

using namespace fibio;
using namespace fibio::http;

std::atomic<bool> should_exit;

void the_client() {
    http_client c;
    http_client::request req;
    std::string req_body("hello");
    req.url="/";
    // Default method
    assert(req.method==http_method::INVALID);
    req.method=http_method::GET;
    // Default version
    assert(req.version==http_version::INVALID);
    req.version=http_version::HTTP_1_1;
    assert(req.get_content_length()==0);
    
    if(c.connect("127.0.0.1", 23456)) {
        assert(false);
    }
    
    for(int i=0; i<100; i++) {
        http_client::response resp;
        if(c.send_request(req, resp)) {
            if (!c.stream_.is_open()) {
                //std::cout << "XXXXXXXX1" << std::endl;
                assert(false);
            }
            if (c.stream_.eof()) {
                //std::cout << "XXXXXXXX2" << std::endl;
                assert(false);
            }
            // This server returns a 200 response
            assert(resp.status_code==http_status_code::OK);
            assert(resp.status_message=="OK");
            assert(resp.version==http_version::HTTP_1_1);
            
            size_t cl=resp.content_length;
            std::string s;
            std::stringstream ss;
            ss << resp.body_stream().rdbuf();
            s=ss.str();
            resp.body_stream().peek();
            assert(s.size()==cl);
            //assert(cl==req_body.size()*2);
            assert(resp.body_stream().eof());
        } else {
            assert(false);
        }
    }
}

typedef boost::asio::basic_waitable_timer<std::chrono::steady_clock> watchdog_timer_t;

void servant_watchdog(watchdog_timer_t &timer, http_server::connection &c) {
    boost::system::error_code ignore_ec;
    while (c.is_open()) {
        timer.async_wait(asio::yield[ignore_ec]);
        // close the stream if timeout
        if (timer.expires_from_now() <= std::chrono::seconds(0)) {
            c.close();
        }
    }
}

void servant(http_server::connection sc) {
    http_server::request req;
    int count=0;
    watchdog_timer_t timer(asio::get_io_service());
    timer.expires_from_now(std::chrono::seconds(3));
    fiber watchdog(servant_watchdog, std::ref(timer), std::ref(sc));
    while(sc.recv(req)) {
        //req.write(std::cout);
        //std::cout.flush();

        std::string s;
        if (req.content_length>0) {
            std::stringstream ss;
            ss << req.body_stream().rdbuf();
            s=ss.str();
        }

        http_server::response resp;
        resp.status_code=http_status_code::OK;
        resp.version=req.version;
        resp.keep_alive=req.keep_alive;
        if(count>=100) resp.keep_alive=false;
        resp.set_content_type("text/html");
        resp.body_stream() << "<HTML><HEAD><TITLE>Test</TITLE></HEAD><BODY><TABLE>" << std::endl;
        for(auto &p: req.headers) {
            resp.body_stream() << "<TR><TD>" << p.first << "</TD><TD>" << p.second << "</TD></TR>" <<std::endl;
        }
        resp.body_stream() << "</TABLE></BODY></HTML>" << std::endl;
        sc.send(resp);
        sc.stream_.flush();
        count++;
    }
    watchdog.join();
}

void main_watchdog(http_server &svr) {
    while (!should_exit) {
        this_fiber::sleep_for(std::chrono::seconds(1));
    }
    svr.close();
}

void the_server() {
    http_server svr(23456, "localhost:23456");
    fiber watchdog(main_watchdog, std::ref(svr));
    boost::system::error_code ec;
    // Check exit flag
    while (!should_exit) {
        http_server::connection sc;
        ec=svr.accept(sc);
        if(ec) break;
        fiber(servant, std::move(sc)).detach();
    }
    watchdog.join();
}

int fibio::main(int argc, char *argv[]) {
    scheduler::get_instance().add_worker_thread(3);

    should_exit=false;
    fiber_group fibers;
    fiber(the_server).detach();
    this_fiber::sleep_for(std::chrono::seconds(1));
    size_t n=10;
    for (int i=0; i<n; i++) {
        fibers.create_fiber(the_client);
    }
    fibers.join_all();
    should_exit=true;
    std::cout << "main_fiber exiting" << std::endl;
    return 0;
}
