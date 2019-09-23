#include <kipr/botball.h>
#include "robo_move.h"

#define LEFT_MOTOR                  0
#define RIGHT_MOTOR                 1
#define LEFT_WALL					5
#define LEFT_TOUCH_SENSOR_D         0
#define RIGHT_TOUCH_SENSOR_D        1
#define LEFT_BOTTOM_IR_SENSOR_A     0
#define LEFT_IR_SENSOR_A            0
#define RIGHT_BOTTOM_IR_SENSOR_A    1
#define RIGHT_IR_SENSOR_A           0
#define LEFT_LIGHT_SENSOR_A         7
#define AMBIENT_LIGHT_SENSOR_A      8
#define RIGHT_LGIHT_SENSOR_A        9
#define DATA_ARRAY_SIZE 			1000

static int goal;
static int ix;
static int responses[DATA_ARRAY_SIZE];
static int leftMotorPowers[DATA_ARRAY_SIZE];
static int rightMotorPowers[DATA_ARRAY_SIZE];

void CalibrateLeftWall();
void primitiveWallFollow();
void primitiveGentleWallFollow();
void proportionalController(float proportionalGain);
void printData(char *dataLabel, int *data, int dataSize);

void CalibrateLeftWall() {
  while (1) {
    int startButton = digital(LEFT_TOUCH_SENSOR_D);
    int stopButton = digital(RIGHT_TOUCH_SENSOR_D);
    int wall = analog(LEFT_WALL);
    printf("goal is %d; wall is %d\n", goal, wall);

    if (startButton) {
        goal = wall;
        beep();
    }

    if (stopButton) {
        printf("Set goal to %d\n", goal);
        beep();
        break;
    }
  }

    msleep(100L);

}

int main() {
//    CalibrateLeftWall();
    demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 100, 100);
    msleep(1000);
    ao();
//    primitiveWallFollow();
//    primitiveGentleWallFollow();
//    proportionalController(0.05);

    return 0;
}

void primitiveWallFollow() {
    ix = 0;

    while(ix < 151) {
        int wall = analog(LEFT_WALL);
        printf("goal is %d; wall is %d\n", goal, wall);

        if (wall < goal) {
            // Go left
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 0, 100);
            leftMotorPowers[ix] = 0;
            rightMotorPowers[ix] = 100;
        } else {
            // Go right
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 100, 0);
            leftMotorPowers[ix] = 100;
            rightMotorPowers[ix] = 0;
        }

        responses[ix] = wall;
        ix++;

        // 10 data points a second.
        msleep(100L);
    }
    ao();
    printData("response", responses, DATA_ARRAY_SIZE);
    printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
    printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}

void primitiveGentleWallFollow() {
    ix = 0;

    while(ix < 151) {
        int wall = analog(LEFT_WALL);
        printf("goal is %d; wall is %d\n", goal, wall);

        if (wall < goal) {
            // Go left
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 50, 100);
            leftMotorPowers[ix] = 50;
            rightMotorPowers[ix] = 100;
        } else {
            // Go right
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 100, 50);
            leftMotorPowers[ix] = 100;
            rightMotorPowers[ix] = 50;
        }

        responses[ix] = wall;
        ix++;

        // 10 data points a second.
        msleep(100L);
    }
    ao();
    printData("response", responses, DATA_ARRAY_SIZE);
    printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
    printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}

void proportionalController(float proportionalGain) {
  ix = 0;
  int error = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int wall = analog(LEFT_WALL);
      printf("goal is %d; wall is %d\n", goal, wall);
      error = goal - wall;

      leftMotorPower = (float) 50 + proportionalGain*(float) error;
      rightMotorPower = (float) 50 - proportionalGain*(float) error;

      if (leftMotorPower < -100) {
        leftMotorPower = -100;
      }

      if (leftMotorPower > 100) {
        leftMotorPower = 100;
      }

      if (rightMotorPower < -100) {
        rightMotorPower = -100;
      }

      if (rightMotorPower > 100) {
        rightMotorPower = 100;
      }

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = wall;
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


void proportionalDerivativeController(float proportionalGain, float derivativeGain) {
  ix = 0;
  int error = 0;
  int lastError = 0;
  float derivativeError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int wall = analog(LEFT_WALL);
      printf("goal is %d; wall is %d\n", goal, wall);
      error = goal - wall;
      derivativeError = (float) error - (float) lastError) / 0.1

      leftMotorPower = (float) 50 + proportionalGain*(float) error + derivativeGain*derivativeError;
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + derivativeGain*derivativeError);

      if (leftMotorPower < -100) {
        leftMotorPower = -100;
      }

      if (leftMotorPower > 100) {
        leftMotorPower = 100;
      }

      if (rightMotorPower < -100) {
        rightMotorPower = -100;
      }

      if (rightMotorPower > 100) {
        rightMotorPower = 100;
      }

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = wall;
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


void proportionalIntegralController(float proportionalGain, float integralGain) {
  ix = 0;
  int error = 0;
  int integralError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int wall = analog(LEFT_WALL);
      printf("goal is %d; wall is %d\n", goal, wall);
      error = goal - wall;
      integralError += error;

      leftMotorPower = (float) 50 + proportionalGain*(float) error + integralGain*integralError);
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + integralGain*integralError);

      if (leftMotorPower < -100) {
        leftMotorPower = -100;
      }

      if (leftMotorPower > 100) {
        leftMotorPower = 100;
      }

      if (rightMotorPower < -100) {
        rightMotorPower = -100;
      }

      if (rightMotorPower > 100) {
        rightMotorPower = 100;
      }

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = wall;
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


void proportionalIntegralDerivativeController(float proportionalGain, float integralGain, float derivativeGain) {
  ix = 0;
  int error = 0;
  int lastError = 0;
  int integralError = 0;
  float derivativeError = 0;
  int leftMotorPower = 0;
  int rightMotorPower = 0;

  while(ix < 151) {
      int wall = analog(LEFT_WALL);
      printf("goal is %d; wall is %d\n", goal, wall);
      error = goal - wall;
      derivativeError = (float) error - (float) lastError) / 0.1
      integralError += error;

      leftMotorPower = (float) 50 + proportionalGain*(float) error + derivativeGain*derivativeError + integralGain*integralError);
      rightMotorPower = (float) 50 - (proportionalGain*(float) error + derivativeGain*derivativeError + integralGain*integralError);

      if (leftMotorPower < -100) {
        leftMotorPower = -100;
      }

      if (leftMotorPower > 100) {
        leftMotorPower = 100;
      }

      if (rightMotorPower < -100) {
        rightMotorPower = -100;
      }

      if (rightMotorPower > 100) {
        rightMotorPower = 100;
      }

      demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

      responses[ix] = wall;
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



void printData(char *dataLabel, int *data, int dataSize) {
    printf("%s : [", dataLabel);
    int dataIndex = 0;
    while(dataIndex++ < dataSize) {
        if(dataIndex < dataSize -1) {
	        printf("%d, ", data[dataIndex]);
        } else {
	        printf("%d", data[dataIndex]);
        }
    }
    printf("]\n");
}
