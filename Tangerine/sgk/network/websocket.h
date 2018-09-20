#pragma once

#include <cstdlib>
#include <iostream>
#include <functional>
#include <memory>
#include <thread>
#include <string>
#include <vector>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/ip/tcp.hpp>

using tcp = boost::asio::ip::tcp;
using error_code = boost::system::error_code;
namespace ws = boost::beast::websocket;
using Websocket = ws::stream<tcp::socket>;

void report_error(error_code ec, char const* what) {
	std::cerr << what << ": " << ec.message() << "\n";
	return;
}




//TODO: ws sgk wrapper