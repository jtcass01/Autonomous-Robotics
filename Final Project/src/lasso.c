#include "lasso.h"

void LassoThread(void) {
  while (1) {
    if ( gv_lassoState == LASSO_STATE_DOWN ) {
      MoveLasso(LASSO_DOWN_ENCODER);
    } else if ( gv_lassoState == LASSO_STATE_UP ) {
      MoveLasso(LASSO_UP_ENCODER);
    }
    wait_for_milliseconds(200);
  }
}


void MoveLasso(int encoderPosition) {
  enable_servos();

  set_servo_position(LASSO_SERVO, encoderPosition);
  msleep(1000);

  disable_servos();
}

void LassoTest(void) {
  MoveLasso(LASSO_DOWN_ENCODER);
  MoveLasso(LASSO_UP_ENCODER);
}
