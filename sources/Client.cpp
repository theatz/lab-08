// "Copyright [year] <Copyright Owner>"
// Created by mrbgn on 3/29/21.
//
#include <Client.hpp>

Client::Client(std::string adr, std::string prt)
    : _adr(adr), _port(prt)
{}

std::string Client::SendRequest(std::string target, std::string id)
{
  // The io_context is required for all I/O
  net::io_context ioc;

// These objects perform our I/O
  tcp::resolver resolver(ioc);
  beast::tcp_stream stream(ioc);

// Look up the domain name
  auto const results = resolver.resolve(_adr, _port);

// Make the connection on the IP address we get from a lookup
  stream.connect(results);

// Set up an HTTP POSt request message
  int version = 11;
  http::request<http::string_body> req{http::verb::post, target, version};
  req.set(http::field::host, _adr);
  req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req.set(beast::http::field::content_type, "text/plain");
  req.body() = FillBody(id);
  req.prepare_payload();

// Send the HTTP request to the remote host
  http::write(stream, req);

// This buffer is used for reading and must be persisted
  beast::flat_buffer buffer;

// Declare a container to hold the response
  http::response<http::dynamic_body> res;

// Receive the HTTP response
  http::read(stream, buffer, res);

// Write the message to standard out
//  std::cout << res << std::endl;

// Gracefully close the socket
  beast::error_code ec;
  stream.socket().shutdown(tcp::socket::shutdown_both, ec);

// not_connected happens sometimes
// so don't bother reporting it.
//
  if(ec && ec != beast::errc::not_connected)
    throw beast::system_error{ec};
// If we get here then the connection is closed gracefully
  std::string s = boost::beast::buffers_to_string(res.body().data());
  return s;
//  return res;
}
std::string Client::FillBody(std::string id) {
  return "input:" + id;
}
