#include <kipr/botball.h>
#include "robo_move.h"

void displayLightReadings(int leftMotor, int rightMotor, int lightSensor1, int lightSensor2);
void NormalizeLightReadings(int lightValue, int minLightValue, int maxLightValue);
void seekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor);
void seekDarkness(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor);
void seekLightAndAvoidObstacles(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int leftTouchSensor, int rightTouchSensor) ;

int main() {
    int leftMotor = 0;
    int rightMotor = 3;
    int leftIRSensorLocation = 0;
    int rightIRSensorLocation = 1;
    int leftTouchSensor = 0;
    int rightTouchSensor = 1;
    int leftLightSensor = 7;
    int middleLightSensor = 8;
    int rightLightSensor = 9;

    return 0;
}

void displayAnalogReadings(int leftMotor, int rightMotor, int lightSensor1, int lightSensor2) {
  while(1) {
    printf("Sensor %d: %d | Sensor %d: %d\n", lightSensor1, lightSensor2, analog(lightSensor1), analog(lightSensor2));
    wait_for_milliseconds(1000);
  }
}

void NormalizeLightReadings(int lightValue, int minLightValue, int maxLightValue) {
    // Apply transform
    int output = 100 - ((lightValue - maxLightValue) * 100) / (minLightValue - maxLightValue);

    // Return value based on range
    if (output < 0) {
      return 0;
    } else if (output > 100) {
      return 100;
    } else {
      return output;
    }
}

void seekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), 0, 4096);
    rightSensorReading = NormalizeLightReadings(analog(rightSensorReading),0, 4096);

    goDemobotMav(leftMotor, rightMotor, 100, leftSensorReading, rightSensorReading);
  }
}

void seekDarkness(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftSensorReading = 100 - NormalizeLightReadings(analog(leftLightSensor), 0, 4096);
    rightSensorReading = 100 - NormalizeLightReadings(analog(rightSensorReading),0, 4096);

    goDemobotMav(leftMotor, rightMotor, 100, leftSensorReading, rightSensorReading);
  }
}

void seekLightAndAvoidObstacles(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int leftTouchSensor, int rightTouchSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;
  int leftTouchSensorReading = 0;
  int rightTouchSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftTouchSensorReading = digital(leftTouchSensor);
    rightTouchSensorReading = digital(rightTouchSensor);
    leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), 0, 4096);
    rightSensorReading = NormalizeLightReadings(analog(rightSensorReading),0, 4096);

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
      goDemobotMav(leftMotor, rightMotor, 100, leftSensorReading, rightSensorReading);
    }
  }
}
