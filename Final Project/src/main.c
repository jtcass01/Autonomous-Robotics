#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_READING_QR;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
int gv_stateFinishedSignal = 0;
int gv_stateFailedSignal = 0;

int main() {
  // Go straightfor 1.5s
  goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1500, 1000, 1000);

  // Make a left turn
  turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

  // Go straightfor 2.5s
  goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 2500, 1000, 1000);

  follow_wall(A_LEFT_LIDAR_WALL_FOLLOW_GOAL_CM);

  return 0;
}
