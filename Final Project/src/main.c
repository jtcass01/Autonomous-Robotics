#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_READING_QR;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
OBJECT_COLOR gv_objectColor = OBJECT_COLOR_INVALID;
int gv_dealingWithButton = 0;

int main() {
  Demo();
  return 0;
}
