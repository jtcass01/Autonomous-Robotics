#include "move.h"

void goDemobot(int leftMotor, int rightMotor, int millisecond_t, int powerLevelLeft, int powerLevelRight) {
    motor(leftMotor, powerLevelLeft);
    motor(rightMotor, powerLevelRight * 0.925);
    msleep(millisecond_t);
    ao();
}
// end goDemobot

void demoMotor(int leftMotor, int rightMotor, int leftMotorPower, int rightMotorPower) {
  motor(leftMotor, leftMotorPower);
  motor(rightMotor, rightMotorPower);
}


void goDemobotMav(int leftMotor, int rightMotor, int millisecond_t, int leftVelocity, int rightVelocity) {
  mav(leftMotor, leftVelocity*0.939);
  mav(rightMotor, rightVelocity);
  msleep(millisecond_t);
  ao();
}

void align_by_analog_sensors(int leftMotor, int rightMotor, int sensorControl1, int sensorControl2, int align_tolerance) {
//  int sensorResponse1 = NormalizeSensorReading(analog(sensorControl1), 170, 250);
//  int sensorResponse2 = NormalizeSensorReading(analog(sensorControl2), 180, 250);
  int sensorResponse1 = analog(sensorControl1);
  int sensorResponse2 = analog(sensorControl2);

  printf("SensorResponse1 = %d  ||  SensorResponse2 = %d", sensorResponse1, sensorResponse2);

  while( sensorResponse1 != sensorResponse2 ) {
    goDemobotMav(leftMotor, rightMotor, 100, -1000, 1000);

    sensorResponse1 = analog(sensorControl1);
    sensorResponse2 = analog(sensorControl2);
    printf("SensorResponse1 = %d  ||  SensorResponse2 = %d", sensorResponse1, sensorResponse2);
  }
}

void SpinForIRReadings(int *readingArray, int numberOfReadings) {
  int index = 0;
  while(index < numberOfReadings) {
    readingArray[index] = analog(A_FRONT_IR);
    goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 3, -800, 800);
    index += 1;
  }
}

void SpinUntilIRReading(int goalValue) {
  int frontReading = analog(A_FRONT_IR);

  printf("Spinning until reading of %d is found.\n", goalValue);
  while(frontReading < goalValue) {
    frontReading = analog(A_FRONT_IR);
    printf("IR Reading %d | goal value %d\n", frontReading, goalValue);
    goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 3, -800, 800);
  }
}

void spin180(int leftMotor, int rightMotor, int clockwise) {
  if (clockwise) {
    goDemobotMav(leftMotor, rightMotor, 1150, 1000, -1000);
  } else {
    goDemobotMav(leftMotor, rightMotor, 1150, -1000, 1000);
  }
  ao();
}

void goStraight(int leftMotor, int rightMotor, int millisecond_t, int powerLevel) {
    goDemobot(leftMotor, rightMotor, millisecond_t, powerLevel, powerLevel);
}

void goStraightMrp(int leftMotor, int rightMotor, int velocity, int numberOfTicks) {
    mrp(leftMotor, velocity*0.944, numberOfTicks);
    mrp(rightMotor, velocity, numberOfTicks);
    msleep(velocity*numberOfTicks);
}

void goStraightMav(int leftMotor, int rightMotor, int millisecond_t, int velocity) {
    mav(leftMotor, velocity*0.939);
    mav(rightMotor, velocity);
    msleep(millisecond_t);
    ao();
}


void make90Turn(int leftMotor, int rightMotor, int leftTurn, int velocity) {
    if(leftTurn) {
        /// Turn 90 degress Left
        goDemobotMav(leftMotor, rightMotor, 1700, 0, velocity);
    } else {
	    /// Turn 90 degrees Right
        goDemobotMav(leftMotor, rightMotor, 1590, velocity, 0);
    }
}

void turnLeft(int leftMotor, int rightMotor) {
  // Turn left
	make90Turn(leftMotor, rightMotor, 1, 750);
}

void turnRight(int leftMotor, int rightMotor) {
  // Turn right
	make90Turn(leftMotor, rightMotor, 0, 750);
}

void reverseLeftTurn(int leftMotor, int rightMotor) {
  // Turn left
  make90Turn(leftMotor, rightMotor, 0, -750);
}

void reverseRightTurn(int leftMotor, int rightMotor) {
  // Turn left
  make90Turn(leftMotor, rightMotor, 1, -750);
}

void driftLeftMav(int leftMotor, int rightMotor, int millisecond_t, int velocity) {
  goDemobotMav(leftMotor, rightMotor, millisecond_t, velocity/30, velocity);
}


void driftRightMav(int leftMotor, int rightMotor, int millisecond_t, int velocity) {
  goDemobotMav(leftMotor, rightMotor, millisecond_t, velocity, velocity/30);
}

void makeCircle(int leftMotor, int rightMotor) {
    goDemobot(leftMotor, rightMotor, 10370, 60, 10);
}

void figureEight(int leftMotor, int rightMotor) {
    goDemobot(leftMotor, rightMotor, 5185, 60, 10);
    goDemobot(leftMotor, rightMotor, 10170, 10, 60);
    goDemobot(leftMotor, rightMotor, 5185, 60, 10);
}
