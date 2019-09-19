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
static int data[DATA_ARRAY_SIZE];

void CalibrateLeftWall();
void primitiveWallFollow();
void primitiveGentleWallFollow();
void proportionalController(float proportionalGain);
void printData(int *data, int dataSize);

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
    CalibrateLeftWall();

//    primitiveWallFollow();
//    primitiveGentleWallFollow();
    proportionalController(0.05);

    return 0;
}

void primitiveWallFollow() {
    ix = 0;

    while(ix < 151) {
        int wall = analog(LEFT_WALL);
        printf("goal is %d; wall is %d\n", goal, wall);

        if (wall < goal) {
            // Go left
            goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 0, 1000);
        } else {
            // Go right
            goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 0);
        }

        data[ix++ % DATA_ARRAY_SIZE] = wall;

        msleep(100L);
    }
    ao();
    printData(data, DATA_ARRAY_SIZE);
}

void primitiveGentleWallFollow() {
    ix = 0;

    while(ix < 151) {
        int wall = analog(LEFT_WALL);
        printf("goal is %d; wall is %d\n", goal, wall);

        if (wall < goal) {
            // Go left
            goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 500, 1000);
        } else {
            // Go right
            goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 500);
        }

        data[ix++ % DATA_ARRAY_SIZE] = wall;

        msleep(100L);
    }
    ao();
    printData(data, DATA_ARRAY_SIZE);
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

      goDemobot(LEFT_MOTOR, RIGHT_MOTOR, 50, leftMotorPower, rightMotorPower);

      data[ix++ % DATA_ARRAY_SIZE] = wall;

      msleep(100L);
  }
  ao();
  printData(data, DATA_ARRAY_SIZE);
}

void printData(int *data, int dataSize) {
    printf("[");
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
