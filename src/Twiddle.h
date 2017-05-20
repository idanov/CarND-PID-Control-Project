#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H

#include "PID.h"

class Twiddle {
private:
  double tolerance;
  int steps;
  int iter;
  int curr;
  double best_err;
  PID pid;
  double p[3] = {0., 0., 0.};
  double dp[3] = {1., 1., 1.};
public:
  Twiddle(double tolerance, int steps);
  double SteerValue(double cte, double speed);
};


#endif //PID_TWIDDLE_H
