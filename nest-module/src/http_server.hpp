#ifndef HTTP_SERVER_HPP
#define HTTP_SERVER_HPP

// #include <cpprest/http_listener.h>
#include <crow/app.h>
#include <crow/http_request.h>
#include <crow/http_response.h>
#include <spdlog/spdlog.h>
#include <future>
#include <memory>
#include <regex>
#include <string>

#undef UNKNOWN
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include "websocketpp/connection.hpp"

typedef websocketpp::client<websocketpp::config::asio_client> client;

namespace insite {

class DataStorage;

class HttpServer {
 public:
  // HttpServer(web::http::uri address, DataStorage* storage);
  HttpServer(std::string address, DataStorage* storage);
  ~HttpServer() {
    app.stop();
  };
  void SimulationHasEnded(double end_time);
  void ClearSimulationHasEnded();

  client::connection_ptr con;
  static bool prepare_finished;
  static int user_id;
  static std::map<int, int> run_no;

 private:
  crow::SimpleApp app;
  std::future<void> crow_server;
  DataStorage* storage_;
  double simulation_end_time_ = -1;

  crow::response GetVersion(const crow::request& request);

  crow::response GetKernelStatus(const crow::request& request);
  crow::response GetKernelStatusV2(const crow::request& request);

  crow::response GetCollections(const crow::request& request);
  crow::response GetCollectionsV2(const crow::request& request);

  crow::response GetNodes(const crow::request& request);
  crow::response GetNodesV2(const crow::request& request);

  crow::response GetSpikeRecorders(const crow::request& request);
  crow::response GetSpikeRecordersV2(const crow::request& request);

  crow::response GetMultimeters(const crow::request& request);
  crow::response GetMultimetersV2(const crow::request& request);

  crow::response GetCurrentSimulationTime(const crow::request& request);
  crow::response GetCurrentSimulationTimeV2(const crow::request& request);

  crow::response GetSpikes(const crow::request& request);
  crow::response GetSpikesV2(const crow::request& request);
  crow::response GetSpikesSendWS(const crow::request& request);
  crow::response GetSpikesFB(const crow::request& request);
  crow::response GetMultimeterMeasurement(const crow::request& request);
  crow::response GetMultimeterMeasurementV2(const crow::request& request);

  struct Error {
    std::string code;
    std::string message;
  };
  std::vector<std::uint64_t> CommaListToUintVector(std::string input, std::regex regex = std::regex("((\\%2C|,)+)"));
};

template <typename T>
T ConvertStringToType(const char* s);

template <>
inline bool ConvertStringToType<bool>(const char* s) {
  return std::stoi(s);
}

template <>
inline uint64_t ConvertStringToType(const char* s) {
  return std::stoull(s);
}

template <>
inline double ConvertStringToType(const char* s) {
  return std::stod(s);
}

template <>
inline std::string ConvertStringToType(const char* s) {
  return s;
}

template <typename T>
T GetParamValueOrDefault(const crow::query_string& query_string, const char* name, T default_value) {
  T result;

  if (query_string.get(name) != nullptr) {
    result = ConvertStringToType<T>(query_string.get(name));
    spdlog::info("{}: {}", name, result);
    return result;
  } else {
    spdlog::info("{}: no value", name);
  }

  return default_value;
}

}  // namespace insite

#endif  // HTTP_SERVER_HPP
