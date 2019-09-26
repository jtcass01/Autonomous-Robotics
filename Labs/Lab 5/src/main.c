#include <kipr/botball.h>
#include "robo_move.h"
#include "constants.h"
#include "pid_control.h"
#include "utilities.h"

void primitiveWallFollow(int goal);
void primitiveGentleWallFollow(int goal);

int main() {
  int goal = 0;

  goal = CalibrateGoal();

  // primitive wall follow
//  primitiveWallFollow(goal);

  // primitiveGentleWallFollow
//  primitiveGentleWallFollow(goal);

  // kp
//  proportionalController(LEFT_WALL, goal, 0.075);

  // kpkd
//  proportionalDerivativeController(LEFT_WALL, goal, 0.02, 0.000076);

  // kpki

  // kpkikd

  return 0;
}

void primitiveWallFollow(int goal) {
  int ix = 0;
  int responses[DATA_ARRAY_SIZE] = {0};
  int leftMotorPowers[DATA_ARRAY_SIZE] = {0};
  int rightMotorPowers[DATA_ARRAY_SIZE] = {0};

  while(ix < 151) {
      // Get data from sensor.
      int wall = analog(LEFT_WALL);
      printf("goal is %d; wall is %d\n", goal, wall);
        if (wall < goal) {
          // Go left
          demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 0, 100);
          // Store motor powers
          leftMotorPowers[ix] = 0;
          rightMotorPowers[ix] = 100;
      } else {
          // Go right
          demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 100, 0);
          // Store motor powers
          leftMotorPowers[ix] = 100;
          rightMotorPowers[ix] = 0;
      }

      responses[ix] = wall;
      ix++;

      // 10 data points a second.
      msleep(100L);
  }
  // Shut off motors.
  ao();
  // Display results.
  printData("response", responses, DATA_ARRAY_SIZE);
  printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
  printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}

void primitiveGentleWallFollow(int goal) {
    ix = 0;

    while(ix < 151) {
        // Get data from sensor.
        int wall = analog(LEFT_WALL);
        printf("goal is %d; wall is %d\n", goal, wall);

        if (wall < goal) {
            // Go left
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 50, 100);
            // Store motor powers
            leftMotorPowers[ix] = 50;
            rightMotorPowers[ix] = 100;
        } else {
            // Go right
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 100, 50);
            // Store motor powers
            leftMotorPowers[ix] = 100;
            rightMotorPowers[ix] = 50;
        }

        // Store sensor response
        responses[ix] = wall;
        // increment data index.
        ix++;

        // 10 data points a second.
        msleep(100L);
    }
    // Shut off motors.
    ao();
    // Display results.
    printData("response", responses, DATA_ARRAY_SIZE);
    printData("leftMotorPower", leftMotorPowers, DATA_ARRAY_SIZE);
    printData("rightMotorPower", rightMotorPowers, DATA_ARRAY_SIZE);
}
