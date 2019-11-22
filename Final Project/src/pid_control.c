#include "pid_control.h"

/*
int CalibrateGoal(int sensorControl) {
  int sensorGoal = 0;

  while (1) {
    int startButton = digital(LEFT_TOUCH_SENSOR_D);
    int stopButton = digital(RIGHT_TOUCH_SENSOR_D);
    int sensorValue = analog(sensorControl);
    printf("goal is %d; senorValue is %d\n", goal, sensorValue);

    if (startButton) {
        goal = sensorValue;
        beep();
    }

    if (stopButton) {
        printf("Set goal to %d\n", goal);
        beep();
        break;
    }

    msleep(100L);
  }

  return goal;
}


void proportionalController(int sensorControl, int sensorGoal, float proportionalGain) {
  int ix = 0;
  int responses[DATA_ARRAY_SIZE] = {0};
  int leftMotorPowers[DATA_ARRAY_SIZE] = {0};
  int rightMotorPowers[DATA_ARRAY_SIZE] = {0};
  int error = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      // Get data from sensor.
      int sensorResponse = analog(sensorControl);
      printf("goal is %d; sensorResponse is %d\n", sensorGoal, sensorResponse);
      // Calculate error.
      error = sensorGoal - sensorResponse;

      // Update motor powers considering proportionalGain.
      leftMotorPower = (float) 50 + proportionalGain*(float) error;
      rightMotorPower = (float) 50 - proportionalGain*(float) error;

      // Ensure powers are bound by [-100, 100]
      leftMotorPower = bind(leftMotorPower, -100, 100);
      rightMotorPower = bind(rightMotorPower, -100, 100);

      // Update motor speed.
      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      // Store response and motor powers.  Update indices
      responses[ix] = sensorResponse;
      leftMotorPowers[ix] = leftMotorPower;
      rightMotorPowers[ix] = rightMotorPower;
      ix++;

      // 10 data points a second.
      msleep(100L);
  }
  ao();
  printData("response", responses, DATA_ARRAY_SIZE);
  printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
  printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}


void proportionalDerivativeController(int sensorControl, int sensorGoal, float proportionalGain, float derivativeGain) {
  int ix = 0;
  int responses[DATA_ARRAY_SIZE] = {0};
  int leftMotorPowers[DATA_ARRAY_SIZE] = {0};
  int rightMotorPowers[DATA_ARRAY_SIZE] = {0};
  int error = 0;
  int lastError = 0;
  float derivativeError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int sensorResponse = analog(sensorControl);
      printf("sensorGoal is %d; sensorResponse is %d\n", sensorGoal, sensorResponse);
      error = sensorGoal - sensorResponse;
      derivativeError = (float) error - (float) lastError) / 0.1;

      leftMotorPower = (float) 50 + proportionalGain*(float) error + derivativeGain*derivativeError;
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + derivativeGain*derivativeError);

      // Ensure powers are bound by [-100, 100]
      leftMotorPower = bind(leftMotorPower, -100, 100);
      rightMotorPower = bind(rightMotorPower, -100, 100);

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = sensorResponse;
      leftMotorPowers[ix] = leftMotorPower;
      rightMotorPowers[ix] = rightMotorPower;
      ix++;

      // 10 data points a second.
      msleep(100L);
  }
  ao();
  printData("response", responses, DATA_ARRAY_SIZE);
  printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
  printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}


void proportionalIntegralController(int sensorControl, int sensorGoal, float proportionalGain, float integralGain) {
  int ix = 0;
  int responses[DATA_ARRAY_SIZE] = {0};
  int leftMotorPowers[DATA_ARRAY_SIZE] = {0};
  int rightMotorPowers[DATA_ARRAY_SIZE] = {0};
  int error = 0;
  int integralError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int sensorResponse = analog(sensorControl);
      printf("sensorGoal is %d; sensorResponse is %d\n", sensorGoal, sensorResponse);
      error = sensorGoal - sensorResponse;
      integralError += error;

      leftMotorPower = (float) 50 + proportionalGain*(float) error + integralGain*integralError;
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + integralGain*integralError);

      // Ensure powers are bound by [-100, 100]
      leftMotorPower = bind(leftMotorPower, -100, 100);
      rightMotorPower = bind(rightMotorPower, -100, 100);

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = sensorResponse;
      leftMotorPowers[ix] = leftMotorPower;
      rightMotorPowers[ix] = rightMotorPower;
      ix++;

      // 10 data points a second.
      msleep(100L);
  }
  ao();
  printData("response", responses, DATA_ARRAY_SIZE);
  printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
  printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}


void proportionalIntegralDerivativeController(int sensorControl, int sensorGoal, float proportionalGain, float integralGain, float derivativeGain) {
  int ix = 0;
  int responses[DATA_ARRAY_SIZE] = {0};
  int leftMotorPowers[DATA_ARRAY_SIZE] = {0};
  int rightMotorPowers[DATA_ARRAY_SIZE] = {0};
  int error = 0;
  int lastError = 0;
  int integralError = 0;
  float derivativeError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int sensorResponse = analog(sensorControl);
      printf("sensorGoal is %d; sensorResponse is %d\n", sensorGoal, sensorResponse);
      error = sensorGoal - sensorResponse;
      derivativeError = (float) error - (float) lastError) / 0.1;
      integralError += error;

      leftMotorPower = (float) 50 + proportionalGain*(float) error + derivativeGain*derivativeError + integralGain*integralError;
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + derivativeGain*derivativeError + integralGain*integralError);

      // Ensure powers are bound by [-100, 100]
      leftMotorPower = bind(leftMotorPower, -100, 100);
      rightMotorPower = bind(rightMotorPower, -100, 100);

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = sensorResponse;
      leftMotorPowers[ix] = leftMotorPower;
      rightMotorPowers[ix] = rightMotorPower;
      ix++;

      // 10 data points a second.
      msleep(100L);
  }
  ao();
  printData("response", responses, DATA_ARRAY_SIZE);
  printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
  printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}
*/
