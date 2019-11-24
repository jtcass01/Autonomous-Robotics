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
        goDemobotMav(leftMotor, rightMotor, 1650, 0, velocity);
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
