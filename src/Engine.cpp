#include <values.h>
#include "Engine.h"
#include <iostream>
#include <valarray>

Engine::Engine(double tolerance, int n_steps) {
  this->best_err = MAXDOUBLE;
  this->iter = 0;
  this->curr = 0;
  this->tolerance = tolerance;
  this->n_steps = n_steps;
  this->twiddle = false;
  if(!this->twiddle) {
    StartRobotRun();
  } else {
    this->curr = -1;
    NextParam();
  }
}

double Engine::SteerValue(double cte, double speed) {
  if(IsRobotRunOver()) {
    FinalizeRobotRun();
  }

  pid.UpdateError(cte);
  double steer_value = speed > 1. ? pid.CalculateCorrection() / speed : 0.;
  steer_value = steer_value <  1. ? steer_value :  1.;
  steer_value = steer_value > -1. ? steer_value : -1.;

  return steer_value;
}

void Engine::FinalizeRobotRun() {
  double err = pid.TotalError();
  if(err < best_err) {
    // If we found a better value for the current parameter
    // update dp and move to the next parameter
    best_err = err;
    dp[curr] *= 1.2;
    NextParam();
  } else {
    if(first_run) {
      // If the first run didn't find a good value, try a second run by decreasing the value with dp
      first_run = false;
      p[curr] -= 2. * dp[curr];
      StartRobotRun();
    } else {
      // If we can't find a better value in this iteration, decrease the delta for the next iteration
      // and move to the next parameter
      p[curr] += dp[curr];
      dp[curr] *= 0.8;
      NextParam();
    }
  }

}

bool Engine::IsRobotRunOver() {
  if(twiddle) {
    bool isCompleted = pid.total_steps >= n_steps;
    bool isOutOfRoad = fabs(pid.p_error) > 4.;
    // Check the error for early stopping of very bad parameters
    bool isErrTooHigh = pid.TotalError() / 10 > best_err;
    return isCompleted || isOutOfRoad || isErrTooHigh;
  } else {
    return false;
  }
}

// Use new parameters and a clean state for the PID controller
void Engine::StartRobotRun() {
  std::cout << "Twiddle PID = [" << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
  pid.Init(p[0], p[1], p[2]);
}

// Print the result of the iteration and decide if we should continue twiddling
void Engine::FinishIteration() {
  std::cout << ">>>>> Iteration #" << iter << ", Best error: " << best_err << std::endl;
  std::cout << ">>>>> PID = [" << p[0] << ", " << p[1] << ", " << p[2] << "]" << std::endl;
  std::cout << ">>>>> PID (delta) = [" << dp[0] << ", " << dp[1] << ", " << dp[2] << "]" << std::endl;
  double s = 0.;
  for(int i = 0; i < 3; i++) s += dp[i];
  // If we've reached very small deltas
  if(s < tolerance) {
    // Stop the twiddling and don't do anymore optimization iterations
    twiddle = false;
  } else {
    // Start a new iteration
    iter++;
  }
}

// Optimize the next parameter with twiddle
void Engine::NextParam() {
  curr++;
  // If we went through all 3 parameters, complete the current iteration
  if(curr >= 3) {
    FinishIteration();
    curr = 0;
  }

  // If we still need to twiddle, initiate the first run for the next parameter
  if(twiddle) {
    first_run = true;
    p[curr] += dp[curr];
  }
  StartRobotRun();
}
