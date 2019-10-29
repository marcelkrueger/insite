#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

#include <cpprest/http_listener.h>
#include <string>

namespace insite {

class DataStorage;

class HttpServer {
 public:
  HttpServer(web::http::uri address, DataStorage* storage);

 private:
  DataStorage* storage_;
  web::http::experimental::listener::http_listener http_listener_;
};

}  // namespace insite

#endif  // HTTP_SERVER_HPP
