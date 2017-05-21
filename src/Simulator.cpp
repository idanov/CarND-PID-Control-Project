#include "Simulator.h"
#include "json.hpp"

// for convenience
using json = nlohmann::json;

Simulator::Simulator(uWS::WebSocket<uWS::SERVER>& ws) {
  this->ws = ws;
}

void Simulator::Steer(double steer_value, double throttle) {
  json msgJson;
  msgJson["steering_angle"] = steer_value;
  msgJson["throttle"] = throttle;
  auto msg = "42[\"steer\"," + msgJson.dump() + "]";
  std::cout << msg << std::endl;
  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
}

void Simulator::Reset() {
  std::string msg = "42[\"reset\",{}]";
  std::cout << msg << std::endl;
  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
}

void Simulator::Manual() {
  std::string msg = "42[\"manual\",{}]";
  std::cout << msg << std::endl;
  ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
}