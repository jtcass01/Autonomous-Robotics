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
  float time_passed = 0.0;

  // Open a connection with the camera.
  camera_open();

  while(1) {
    switch(gv_robotState) {
      case ROBOT_STATE_READING_QR:
        printf("ROBOT_STATE_READING_QR\n");

        // Go straightfor .5s
        printf("Drive straight for 1.75s\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 2000, 1000, 1000);

        // Make a left turn
        printf("Making a left turn.\n");
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

        // Go straight until the buttons are pressed
        printf("Going straight until buttons are pressed.\n");
        while(!gv_dealingWithButton) {
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 1000, 1000);
        }
        ao();

        printf("Backing up for 1s.\n");
        // back up for 1 second
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

        printf("Turning left.\n");
        // Turn left
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);

        // go straight for 1 second
        printf("going straight for 1.35 second\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1350, 1000, 1000);

        // Read QR code
        while(gv_objectColor == OBJECT_COLOR_INVALID) {
          // Turn off motors
          ao();

          // spend 3.5 seconds looking for QR code
          while(time_passed < 3.5) {
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
              if (time_passed < 0.6) {
                // pan right
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 100, -100);
              } else if (time_passed < 1.8) {
                // pan left
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, -100, 100);
              } else if (time_passed < 2.4) {
                // pan back center
                goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, 100, -100);
              } else {
                ao();
              }
            }
            wait_for_milliseconds(100);
            time_passed += 0.1;
          }

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
              printf("Driving fowards for 0.2s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 200, 1000, 1000);

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
              printf("Driving fowards for 0.2s.\n");
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 200, 1000, 1000);

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
        printf("Driving fowards for 0.3s.\n");
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 200, 1000, 1000);
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
        } else {
          printf("Roaming. Performing circle until object is found");
          goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 100, -1000, 1000);
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

            // report to executive and give it time to react.
            printf("Object lassoed.\n");
            gv_robotState = ROBOT_STATE_APPROACHING_GOAL;
          } else {
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
          }
        }
        break;
      case ROBOT_STATE_APPROACHING_GOAL:
        printf("ROBOT_STATE_APPROACHING_GOAL\n");
        align_by_analog_sensors(LEFT_MOTOR, RIGHT_MOTOR, A_FRONT_LEFT_IR, A_FRONT_RIGHT_IR, 10);
        break;
      case ROBOT_STATE_PLACING_OBJECT:
        printf("ROBOT_STATE_PLACING_OBJECT\n");
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
  int firstPress = 0;

  while(1) {
    // get sensor readings
    frontLeftButtonReading = digital(D_FRONT_LEFT_BUTTON);
    frontRightButtonReading = digital(D_FRONT_RIGHT_BUTTON);

    if (gv_robotState == ROBOT_STATE_READING_QR) {
      if ((frontLeftButtonReading || frontRightButtonReading) && firstPress == 0) {
        gv_dealingWithButton = 1;
        firstPress += 1;
        wait_for_milliseconds(1000);
        gv_dealingWithButton = 0;
      }
    } else {
      if (frontLeftButtonReading && frontRightButtonReading) {
        gv_dealingWithButton = 1;
        ao();
        // back up 1s
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

        // turn around
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);
        gv_dealingWithButton = 0;
      } else if (frontLeftButtonReading) {
        gv_dealingWithButton = 1;
        ao();
        // back up 1s
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

        // turn around
        turnRight(LEFT_MOTOR, RIGHT_MOTOR);
        gv_dealingWithButton = 0;
      } else if (frontRightButtonReading) {
        gv_dealingWithButton = 1;
        ao();
        // back up 1s
        goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1000, -1000, -1000);

        // turn around
        turnLeft(LEFT_MOTOR, RIGHT_MOTOR);
        gv_dealingWithButton = 0;
      }
    }
    wait_for_milliseconds(1000);
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
