
#ifndef PID_CONTROL_H
#define PID_CONTROL_H

#include <kipr/botball.h>
#include "constants.h"
#include "utilities.h"

int CalibrateGoal(int sensorControl);
void proportionalController(int sensorControl, int sensorGoal, float proportionalGain);
void proportionalDerivativeController(int sensorControl, int sensorGoal, float proportionalGain, float derivativeGain);
void proportionalIntegralController(int sensorControl, int sensorGoal, float proportionalGain, float integralGain);
void proportionalIntegralDerivativeController(int sensorControl, int sensorGoal, float proportionalGain, float integralGain, float derivativeGain);

#endif
