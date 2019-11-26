#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_READING_QR;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
OBJECT_COLOR gv_objectColor = OBJECT_COLOR_INVALID;
HOME_BASE gv_homeBase = HOME_BASE_BLACK;
int gv_dealingWithButton = 0;

int main() {
  spin180(LEFT_MOTOR, RIGHT_MOTOR, 0);
  return 0;
}
