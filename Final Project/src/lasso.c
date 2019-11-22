#include "lasso.h"

void LassoThread(void) {
  while (1) {
    if ( gv_lassoState == LASSO_STATE_DOWN ) {
      LowerLasso();

      gv_lassoState = LASSO_STATE_WAITING;
    } else if ( gv_lassoState == LASSO_STATE_UP ) {
      RaiseLasso();

      gv_lassoState = LASSO_STATE_WAITING;
    } else {
      wait_for_milliseconds(200);
    }
  }
}

void LowerLasso(void) {
  enable_servos();

  set_servo_position(LASSO_SERVO, LASSO_DOWN_ENCODER);
  msleep(1000);

  disable_servos();
}

void RaiseLasso(void) {
  enable_servos();

  set_servo_position(LASSO_SERVO, LASSO_UP_ENCODER);
  msleep(1000);

  disable_servos();
}

void LassoTest(void) {
  LowerLasso();
  RaiseLasso();
}
