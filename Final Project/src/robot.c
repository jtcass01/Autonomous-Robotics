#include "robot.h"

void Demo(void) {
  // wait for start button to begin.
  while (any_button() == 0);
  printf("Beginning Demo.\n");

  // create threads
  thread driveThread = thread_create(DriveThread);
  thread lassoThread = thread_create(LassoThread);
  thread buttonThread = thread_create(ButtonThread);

  // start threads
  thread_start(driveThread);
  thread_start(lassoThread);
  thread_start(buttonThread);

  // Run for 5 minutes
  wait_for_milliseconds(60000 * 2);

  // Destroy threads
  thread_destroy(driveThread);
  thread_destroy(lassoThread);
  thread_destroy(buttonThread);
}

void DriveThread(void) {
  int leftMotorPower = 0;
  int rightMotorPower = 0;
  int objectCount = 0;
  int leftLook = 1;
  int IRSpinReadings[NUM_IR_SPIN_READINGS];
  float time_passed = 0.0;

  if (analog(A_FRONT_IR) > 2000) {
    gv_homeBase = HOME_BASE_WHITE;
    printf("The home base is thought to be white\n");
  } else {
    gv_homeBase = HOME_BASE_BLACK;
    printf("The home base is thought to be black.\n");
  }


  // Open a connection with the camera.
  camera_open();

  while(1) {
    switch(gv_robotState) {
      case ROBOT_STATE_READING_QR:
        printf("ROBOT_STATE_READING_QR\n");

        // Go straightfor .5s
        printf("Drive straight for 0.2s\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 200, 1000, 1000);

        // Make a left turn
        printf("Making a left turn.\n");
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

        // Go straight until the buttons are pressed
        printf("Going straight until buttons are pressed.\n");
        while(!gv_dealingWithFrontButton) {
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 50, 1000, 1000);
        }
        ao();

        printf("Performing reverseLeftTurn.\n");
        // Turn left
        reverseLeftTurn(LEFT_MOTOR, RIGHT_MOTOR);

        printf("Attempting to read QR code\n");

        // Read QR code
        while(gv_objectColor == OBJECT_COLOR_INVALID) {
          // Turn off motors
          ao();

          // spend 3.5 seconds looking for QR code
          while(time_passed < 6) {
            wait_for_milliseconds(100);
            camera_update();

            if (get_object_count(QR_CHANNEL_NUMBER) > 0) {
              if (strcmp("green", get_object_data(QR_CHANNEL_NUMBER, 0)) == 0) {
                printf("Object color is green.\n");
                gv_objectColor = OBJECT_COLOR_GREEN;
                break;
              } else if (strcmp("orange", get_object_data(QR_CHANNEL_NUMBER, 0)) == 0) {
                printf("Object color is orange.\n");
                gv_objectColor = OBJECT_COLOR_ORANGE;
                break;
              } else if (strcmp("purple", get_object_data(QR_CHANNEL_NUMBER, 0)) == 0) {
                printf("Object color is purple.\n");
                gv_objectColor = OBJECT_COLOR_PURPLE;
                break;
              } else {
                printf("Object color is not recognized.\n");
                gv_objectColor = OBJECT_COLOR_INVALID;
              }
            } else {
              printf("No QR Code found.\n");
              if (time_passed < 1.5) {
                // pan right
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 150, -150);
              } else if (time_passed < 4) {
                // pan left
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, -150, 150);
              } else if (time_passed < 6) {
                // pan back center
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 150, -150);
              }
            }
            time_passed += 0.1;
          }
          ao();
          time_passed = 0;

          if (gv_objectColor == OBJECT_COLOR_INVALID) {
            if (leftLook) {
              // Drive back for 1s
              printf("Driving backwards for 1s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

              printf("Turning left.\n");
              turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

              printf("Turning right.\n");
              turnRight(LEFT_MOTOR, RIGHT_MOTOR);

              // Drive forward for 1s
              printf("Driving fowards for 0.1s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 1000);

              leftLook = 0;
            } else {
              // Drive back for 1s
              printf("Driving backwards for 1s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

              printf("Turning right.\n");
              turnRight(LEFT_MOTOR, RIGHT_MOTOR);

              printf("Turning left.\n");
              turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

              // Drive forward for 1s
              printf("Driving fowards for 0.1s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 1000);

              leftLook = 1;
            }
          }
        }

        ao();
        gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;

        // Drive back for 1s
        printf("Driving backwards for 1.5s.\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1500, -1000, -1000);

        // turn left
        printf("Turning left.\n");
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

        // Drive forward .3 second
        printf("Driving fowards for 0.3.\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 300, 1000, 1000);
        break;

      case ROBOT_STATE_SEARCHING_FOR_OBJECT:
        printf("ROBOT_STATE_SEARCHING_FOR_OBJECT\n");
        // Update the camera image
        camera_update();

        // Get the object count
        objectCount = get_object_count(gv_objectColor);

        if (objectCount > 0) {
          printf("Object found.\n");
          ao();
          gv_robotState = ROBOT_STATE_APPROACHING_OBJECT;
          time_passed = 0;
        } else {
          if (time_passed < 6 ) {
              printf("Roaming. Performing circle until object is found\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, -1000, 1000);
              time_passed += 0.1;
          } else {
              printf("Too much circle talk.  Driving forward until button is pressed.\n");
              time_passed = 0;

              while(!gv_dealingWithFrontButton) {
		              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 1000);
              }

              printf("Driving backwards for 2s\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 2000, -1000, -1000);
              printf("spin180 CW\n");
              spin180(LEFT_MOTOR, RIGHT_MOTOR, 1);
          }
        }
        break;
      case ROBOT_STATE_APPROACHING_OBJECT:
        printf("ROBOT_STATE_APPROACHING_OBJECT\n");
        // Update the camera image
        camera_update();

        // Get the object count
        objectCount = get_object_count(gv_objectColor);

        if (objectCount <= 0) {
          printf("Object lost.\n");
          ao();
          gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
        } else {
          if (UpdateMotorPowers_TrackObject(&leftMotorPower, &rightMotorPower) == 0) {
            // shut off motors.
            ao();

            // command lasso to down state.
            gv_lassoState = LASSO_STATE_DOWN;
            wait_for_milliseconds(1500);

            // report to executive and give it time to react.
            printf("Object lassoed.\n");
            gv_robotState = ROBOT_STATE_APPROACHING_GOAL;
          } else {
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
          }
        }

        if (gv_homeBase == HOME_BASE_WHITE) {
          printf("Inside white home base.  Leaving Base.\n");
          if (analog(A_FRONT_IR) < WHITE_THRESHOLD) {
            gv_robotState = ROBOT_STATE_LEAVING_BASE;
          }
        } else {
          printf("Inside black home base.  Leaving Base.\n");
          if (analog(A_FRONT_IR) > BLACK_THRESHOLD) {
            gv_robotState = ROBOT_STATE_LEAVING_BASE;
          }
        }

        break;
      case ROBOT_STATE_APPROACHING_GOAL:
        printf("ROBOT_STATE_APPROACHING_GOAL\n");
        // spinning for IR Readings
        SpinForIRReadings(IRSpinReadings, NUM_IR_SPIN_READINGS);
        BubbleSort(IRSpinReadings, NUM_IR_SPIN_READINGS);

        while ( IRSpinReadings[NUM_IR_SPIN_READINGS-1] - IRSpinReadings[0] > 1100 ) {
          printf("Near center Line.\n");

          if (gv_homeBase == HOME_BASE_WHITE) {
            printf("Home base White. Heading towards darker side then respinning.\n");
            SpinUntilIRReading(IRSpinReadings[ (int) (NUM_IR_SPIN_READINGS / 2)], 0);
          } else {
            printf("Home base black. Heading towards lighter side then respinning.\n");
            SpinUntilIRReading(IRSpinReadings[ (int) (NUM_IR_SPIN_READINGS / 2)], 1);
          }

          printf("Driving forward 0.5s\n");
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 700, 1000, 1000);

          printf("Respinning for readings.\n");
          SpinForIRReadings(IRSpinReadings, NUM_IR_SPIN_READINGS);
        }

        SpinUntilIRReading(IRSpinReadings[NUM_IR_SPIN_READINGS-2], 0);
        ao();
        if (gv_homeBase == HOME_BASE_WHITE) {
          printf("On white side.  Spinning 180 CW.\n");
          spin180(LEFT_MOTOR, RIGHT_MOTOR, 1);
        }

        printf("Spinning 30 degrees to even up back");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 200, -1000, 1000);

        printf("Driving backwards until button is pressed.\n");
        while( !gv_dealingWithBackButton ) {
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, -1000, -1000);
        }

        // turn a lil left for good measure
        printf("turning a lil left for good measure.\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 10, 100, 1000);

        printf("Driving forwards for 0.9 second\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 900, 1000, 1000);

        printf("Performing reverse left turn\n");
        reverseLeftTurn(LEFT_MOTOR, RIGHT_MOTOR);

        // raise lasso
        gv_lassoState = LASSO_STATE_UP;

        // Drive forward until a button is pressed
        while(!gv_dealingWithFrontButton) {
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 50, 1000, 1000);
        }


        if (gv_homeBase == HOME_BASE_WHITE) {
          if (analog(A_FRONT_IR) > WHITE_THRESHOLD) {
            printf("Not inside home base.  Backing up with block and respinning.\n");
          }
        } else {
          if (analog(A_FRONT_IR) < BLACK_THRESHOLD) {
            printf("Not inside home base.  Backing up with block and respinning.\n");
          }
        }

        gv_robotState = ROBOT_STATE_LEAVING_BASE;
        break;
      case ROBOT_STATE_LEAVING_BASE:
        printf("ROBOT_STATE_LEAVING_BASE\n");
        printf("Driving backwards for 4s\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 4000, -1000, -1000);

        printf("Spinning 180 CW\n");
        spin180(LEFT_MOTOR, RIGHT_MOTOR, 1);

        printf("Turning Left\n");
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

        gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
        break;
      case ROBOT_STATE_INVALID:
        printf("ROBOT_STATE_INVALID\n");
        // Raise error.
        break;
    }
  }
  wait_for_milliseconds(100);
}

void ButtonThread(void) {
  int frontLeftButtonReading = 0;
  int frontRightButtonReading = 0;
  int backLeftButtonReading = 0;
  int backRightButtonReading = 0;

  while(1) {
    // get sensor readings
    frontLeftButtonReading = digital(D_FRONT_LEFT_BUTTON);
    frontRightButtonReading = digital(D_FRONT_RIGHT_BUTTON);
    backLeftButtonReading = digital(D_BACK_LEFT_BUTTON);
    backRightButtonReading = digital(D_BACK_RIGHT_BUTTON);

    if (frontLeftButtonReading || frontRightButtonReading) {
      gv_dealingWithFrontButton = 1;
      wait_for_milliseconds(1000);
      gv_dealingWithFrontButton = 0;
    }

    if (backLeftButtonReading || backRightButtonReading) {
      gv_dealingWithBackButton = 1;
      wait_for_milliseconds(1000);
      gv_dealingWithBackButton = 0;
    }

    wait_for_milliseconds(100);
  }
}




int UpdateMotorPowers_TrackObject(int *leftMotorPower, int *rightMotorPower) {
  int objectXLocation = 0;
  int objectYLocation = 0;
  int yPowerComponent = 0;

  objectXLocation = get_object_center_x(gv_objectColor, 0);
  objectYLocation = get_object_center_y(gv_objectColor, 0);

  // Check if the objectYLocation is outside of the tolerance
  if (objectYLocation < OBJECT_LASSO_Y_CAP) {
    // Object is too far away
    yPowerComponent = 100 - NormalizeSensorReading(objectYLocation, 0, OBJECT_LASSO_Y_CAP);
    *leftMotorPower += yPowerComponent;
    *rightMotorPower += yPowerComponent;
  }

  *leftMotorPower /= 2;
  *rightMotorPower /= 2;

  // Check if the objectXLocation is outside of the tolerance
  if ( objectXLocation < OBJECT_X_GOAL - OBJECT_LASSO_X_TOLERANCE || objectXLocation > OBJECT_X_GOAL - OBJECT_LASSO_X_TOLERANCE ) {
    if (objectXLocation < OBJECT_X_GOAL) {
      // Object is to the left.
      *rightMotorPower += 100 - NormalizeSensorReading(objectXLocation, 0, OBJECT_X_GOAL);
    } else {
      // Object is to the right.
      *leftMotorPower += NormalizeSensorReading(objectXLocation, OBJECT_X_GOAL, IMAGE_WIDTH);
    }
  }

  *leftMotorPower = bind(*leftMotorPower, -100, 100);
  *rightMotorPower = bind(*rightMotorPower, -100, 100);

  return yPowerComponent;
}
