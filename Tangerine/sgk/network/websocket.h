#pragma once
#pragma warning(disable:4996)

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
#include <boost/asio/io_context.hpp>

namespace ip = boost::asio::ip;
using tcp = ip::tcp;
using error_code = boost::system::error_code;
namespace ws = boost::beast::websocket;
using Websocket = ws::stream<tcp::socket>;
using IO_Context = boost::asio::io_context;

inline void report_error(error_code ec, char const* what) {
	std::cerr << what << ": " << ec.message() << "\n";
	return;
}




//TODO: ws sgk wrapper