#ifndef PID_TWIDDLE_H
#define PID_TWIDDLE_H

#include "PID.h"

class Engine {
private:
  double tolerance;
  int n_steps;
  int iter;
  int curr;
  double best_err;
  PID pid;
  double p[3] = {5., 0.001, 50.};
  double dp[3] = {.5, .01, .3};

  bool twiddle;
  bool first_run;
  void FinishIteration();
  void FinalizeRobotRun();
  void StartRobotRun();
  void NextParam();
public:
  Engine(double tolerance, int n_steps);
  double SteerValue(double cte, double speed);
  bool IsRobotRunOver();
};


#endif //PID_TWIDDLE_H
