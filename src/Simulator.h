#ifndef PID_SIMULATOR_H
#define PID_SIMULATOR_H


#include <uWS/uWS.h>

class Simulator {

private:
  uWS::WebSocket<uWS::SERVER> ws;

public:
  /*
  * Constructor
  */
  Simulator(uWS::WebSocket<uWS::SERVER>& ws);

  void Reset();

  void Steer(double steer_value, double throttle);

  void Manual();
};


#endif //PID_SIMULATOR_H
