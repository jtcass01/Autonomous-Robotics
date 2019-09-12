#include <kipr/botball.h>
#include "robo_move.h"

void driveForward(int leftMotorLocation, int rightMotorLocation, int velocity);
void turtleMode(int leftMotor, int rightMotor, int leftTouchSensor, int rightTouchSensor);
void lineFollower(int leftMotor, int rightMotor, int leftIRSensorLocation, int rightIRSensorLocation);
void lineFollowerBlocker(int leftMotor, int rightMotor, int leftIRSensor, int rightIRSensor, int leftTouchSensor, int rightTouchSensor);

int main() {
    int leftMotor = 0;
    int rightMotor = 3;
    int leftIRSensorLocation = 0;
    int rightIRSensorLocation = 1;
    int leftTouchSensor = 0;
    int rightTouchSensor = 1;

    lineFollowerBlocker(leftMotor, rightMotor, leftIRSensorLocation, rightIRSensorLocation, leftTouchSensor, rightTouchSensor);
    return 0;
}

void driveForward(int leftMotorLocation, int rightMotorLocation, int velocity) {
    mav(leftMotorLocation, velocity);
    mav(rightMotorLocation, velocity);
}

void turtleMode(int leftMotor, int rightMotor, int leftTouchSensor, int rightTouchSensor) {
    // Initialize variables
    int leftSensorReading = 0;
    int rightSensorReading = 0;
    while(1) {
        // Get sensor data
        leftSensorReading = digital(leftTouchSensor);
        rightSensorReading = digital(rightTouchSensor);
        if(leftTouchSensorReading) {
          // Back up
          goStraightMav(leftMotor, rightMotor, 1000, -500);
          // Turn Right 90
          turnRight(leftMotor, rightMotor);
          // Go straight
          goStraightMav(leftMotor, rightMotor, 500, 500);
          // Turn left
          turnLeft(leftMotor, rightMotor);
        } else if (rightTouchSensorReading) {
          // Back up
          goStraightMav(leftMotor, rightMotor, 1000, -500);
          // Turn left 90
          turnLeft(leftMotor, rightMotor);
          // Go straight
          goStraightMav(leftMotor, rightMotor, 500, 500);
          // Back up
          turnRight(leftMotor, rightMotor);
        } else {
          // Go straight
          goStraightMav(leftMotor, rightMotor, 500, 500);
        }
    }
}

void lineFollower(int leftMotor, int rightMotor, int leftIRSensorLocation, int rightIRSensorLocation) {
    int leftIRReading = 0;
    int rightIRReading = 0;
    int difference = 0;
    int differenceThreshhold = 400;

    while(1) {
        // Get sensor reading
        leftIRReading = analog(leftIRSensorLocation);
        rightIRReading = analog(rightIRSensorLocation);

        // Calculate difference
        difference = leftIRReading - rightIRReading;

        if(difference > differenceThreshhold || difference < (differenceThreshhold*-1)) {
            if(difference > 0) {
                // Drift leftwards
                driftLeftMav(leftMotor, rightMotor, 50, 100);
            } else {
                // Drift rightwards
                driftRightMav(leftMotor, rightMotor, 50, 100);
            }
        } else {
          // Continue straight
          goStraightMav(leftMotor, rightMotor, 50, 100);
        }
    }
}

void lineFollowerBlocker(int leftMotor, int rightMotor, int leftIRSensor, int rightIRSensor,
   int leftTouchSensor, int rightTouchSensor) {
    // Initialize variables
    int leftIRReading = 0;
    int rightIRReading = 0;
    int leftTouchSensorReading = 0;
    int rightTouchSensorReading = 0;
    int difference = 0;
    int differenceThreshhold = 400;

    while(1) {
        // Get sensor reading
        leftIRReading = analog(leftIRSensor);
        rightIRReading = analog(rightIRSensor);
        leftTouchSensorReading = digital(leftTouchSensor);
        rightTouchSensorReading = digital(rightTouchSensor);

        // Calculate difference between IR sensors
        difference = leftIRReading - rightIRReading;

        if(leftTouchSensorReading) {
            // back up
            goStraightMav(leftMotor, rightMotor, 1000, -500);
            // Turn right 90
            turnRight(leftMotor, rightMotor);
            // Go forward some
            goStraightMav(leftMotor, rightMotor, 500, 500);
            // Turn left 90
            turnLeft(leftMotor, rightMotor);
        } else if (rightTouchSensorReading) {
            // back up
            goStraightMav(leftMotor, rightMotor, 1000, -500);
            // Turn left 90
            turnLeft(leftMotor, rightMotor);
            // Go forward some
            goStraightMav(leftMotor, rightMotor, 500, 500);
            // Turn right 90
            turnRight(leftMotor, rightMotor);
        } else {
            // Same as line follower code
            if(difference > differenceThreshhold || difference < (differenceThreshhold*-1)) {
                if(difference > 0) {
                    // We need to drift left
                    driftLeftMav(leftMotor, rightMotor, 50, 200);
                } else {
                    // We need to drift right
                    driftRightMav(leftMotor, rightMotor, 50, 200);
                }
            } else {
              // Continue straight
              goStraightMav(leftMotor, rightMotor, 50, 300);
            }
        }
    }
}
