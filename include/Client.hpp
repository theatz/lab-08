// "Copyright [year] <Copyright Owner>"
// Created by mrbgn on 3/29/21.
//

#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

#ifndef INCLUDE_CLIENT_HPP_
#define INCLUDE_CLIENT_HPP_

class Client
{
 public:
  Client(std::string adr, std::string prt);
  std::string SendRequest(std::string target, std::string id);
  std::string FillBody(std::string id);

 private:
  std::string _adr;
  std::string _port;
};


#endif  // INCLUDE_CLIENT_HPP_
