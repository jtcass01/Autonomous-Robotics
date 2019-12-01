#include "robot.h"

// Initialize global variables
ROBOT_STATE gv_robotState = ROBOT_STATE_READING_QR;
LASSO_STATE gv_lassoState = LASSO_STATE_UP;
OBJECT_COLOR gv_objectColor = OBJECT_COLOR_INVALID;
HOME_BASE gv_homeBase = HOME_BASE_BLACK;
int gv_dealingWithFrontButton = 0;
int gv_dealingWithBackButton = 0;

int main() {
  int readings[NUM_IR_SPIN_READINGS];
  SpinForIRReadings(readings, NUM_IR_SPIN_READINGS);
  return 0;
}
