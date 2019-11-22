#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_READING_QR;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
int gv_stateFinishedSignal = 0;
int gv_stateFailedSignal = 0;

int main() {
  ReportAnalogSensorValues(A_FRONT_SONAR);
  return 0;
}
