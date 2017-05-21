#include "PID.h"

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;
  this->err = 0;
  this->total_steps = 0;
}

void PID::UpdateError(double cte) {
    this->d_error = cte - this->p_error;
    this->i_error += cte;
    this->p_error = cte;
    this->total_steps++;
    this->err += cte * cte;
}

double PID::TotalError() {
  return this->total_steps > 0 ? this->err / this->total_steps : 0;
}

double PID::CalculateCorrection() {
  return -this->Kp * this->p_error - this->Kd * this->d_error - this->Ki * this->i_error;
}
