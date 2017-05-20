#include "Twiddle.h"

Twiddle::Twiddle(double tolerance, int steps) {
  this->tolerance = tolerance;
  this->steps = steps;
  this->pid.Init(5.0, 0.01, 30.0);
}

double Twiddle::SteerValue(double cte, double speed) {
  pid.UpdateError(cte);
  double steer_value = speed > 1. ? pid.TotalError() / speed : 0.;
  steer_value = steer_value <  1. ? steer_value :  1.;
  steer_value = steer_value > -1. ? steer_value : -1.;
  return steer_value;
}