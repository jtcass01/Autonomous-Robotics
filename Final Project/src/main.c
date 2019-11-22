#include <kipr/botball.h>
#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
RunningAverage gv_ra_x = {0};
RunningAverage gv_ra_y = {0};
int gv_lastObjectX = 0;
int gv_lastObjectY = 0;
int gv_lastObjectCount = 0;
int gv_stateFinishedSignal = 0;
int gv_stateFailedSignal = 0;

int main() {
  Demo();
  return 0;
}
