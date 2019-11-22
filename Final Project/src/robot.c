#include "robot.h"

void Demo(void) {
  // create threads
  thread executiveThread = thread_create(ExecutiveThread);
  thread driveThread = thread_create(DriveThread);
  thread lassoThread = thread_create(LassoThread);

  // start threads
  thread_start(executiveThread);
  thread_start(driveThread);
  thread_start(lassoThread);

  // Run for 5 minutes
  wait_for_milliseconds(60000 * 2);

  // Destroy threads
  thread_destroy(executiveThread);
//  thread_destroy(cameraThread);
  thread_destroy(lassoThread);
}


void ExecutiveThread(void) {
  while(1) {
    switch(gv_robotState) {
      case ROBOT_STATE_READING_QR:
        printf("ROBOT_STATE_READING_QR....\n");
        break;
      case ROBOT_STATE_SEARCHING_FOR_OBJECT:
        printf("ROBOT_STATE_SEARCHING_FOR_OBJECT....\n");
        break;
      case ROBOT_STATE_APPROACHING_OBJECT:
        printf("ROBOT_STATE_APPROACHING_OBJECT....\n");
        break;
      case ROBOT_STATE_APPROACHING_GOAL:
        printf("ROBOT_STATE_APPROACHING_GOAL....\n");
        break;
      case ROBOT_STATE_PLACING_OBJECT:
        printf("ROBOT_STATE_PLACING_OBJECT....\n");
        break;
      case ROBOT_STATE_INVALID:
        printf("ROBOT_STATE_INVALID....\n");
        break;
    }

    if (gv_stateFinishedSignal) {
      switch(gv_robotState) {
          case ROBOT_STATE_READING_QR:
            gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
            break;
          case ROBOT_STATE_SEARCHING_FOR_OBJECT:
            gv_robotState = ROBOT_STATE_APPROACHING_OBJECT;
            break;
          case ROBOT_STATE_APPROACHING_OBJECT:
            gv_robotState = ROBOT_STATE_APPROACHING_GOAL;
            break;
          case ROBOT_STATE_APPROACHING_GOAL:
            gv_robotState = ROBOT_STATE_PLACING_OBJECT;
            break;
          case ROBOT_STATE_PLACING_OBJECT:
            gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
            break;
          case ROBOT_STATE_INVALID:
            break;
      }
      gv_stateFinishedSignal = 0;
    } else if (gv_stateFailedSignal) {
      switch(gv_robotState) {
          case ROBOT_STATE_READING_QR:
          case ROBOT_STATE_SEARCHING_FOR_OBJECT:
          case ROBOT_STATE_APPROACHING_OBJECT:
          case ROBOT_STATE_APPROACHING_GOAL:
          case ROBOT_STATE_PLACING_OBJECT:
            gv_robotState = ROBOT_STATE_SEARCHING_FOR_OBJECT;
            break;
          case ROBOT_STATE_INVALID:
            break;
      }
      gv_stateFailedSignal = 0;
    }
  }
  wait_for_milliseconds(1000);
}

void DriveThread(void) {
  int leftMotorPower = 0;
  int rightMotorPower = 0;
  int objectCount = 0;
  ROBOT_STATE_READING_QR_SUBSTATE readingQRSubstate = ROBOT_STATE_READING_QR_SUBSTATE_FINDING_WALL;

  // Open a connection with the camera.
  camera_open();

  while(1) {
    switch(gv_robotState) {
      case ROBOT_STATE_READING_QR:
        // Update the camera image
        camera_update();

        switch(readingQRSubstate) {
          case ROBOT_STATE_READING_QR_SUBSTATE_FINDING_WALL:
            readingQRSubstate = ROBOT_STATE_READING_QR_SUBSTATE_FOLLOWING_WALL;
            break;
          case ROBOT_STATE_READING_QR_SUBSTATE_FOLLOWING_WALL:
            readingQRSubstate = ROBOT_STATE_READING_QR_SUBSTATE_APPROACHING_QR;
            break;
          case ROBOT_STATE_READING_QR_SUBSTATE_APPROACHING_QR:
            readingQRSubstate = ROBOT_STATE_READING_QR_SUBSTATE_TAKING_READING;
            break;
          case ROBOT_STATE_READING_QR_SUBSTATE_TAKING_READING:
            printf("QR code read.\n");
            gv_stateFinishedSignal = 1;
            wait_for_milliseconds(1000);
            break;
          case ROBOT_STATE_READING_QR_SUBSTATE_INVALID:
            readingQRSubstate = ROBOT_STATE_READING_QR_SUBSTATE_FINDING_WALL;
            break;
        }
        break;

      case ROBOT_STATE_SEARCHING_FOR_OBJECT:
        // Update the camera image
        camera_update();

        // Get the object count
        objectCount = get_object_count(OBJECT_CHANNEL_NUMBER);

        if (objectCount > 0) {
          printf("Object found.\n");
          ao();
          gv_stateFinishedSignal = 1;
          wait_for_milliseconds(1000);
        } else {
          // pan to the left
          demoMotor(LEFT_MOTOR, RIGHT_MOTOR, 0, 20);
        }
        break;
      case ROBOT_STATE_APPROACHING_OBJECT:
        // Update the camera image
        camera_update();

        // Get the object count
        objectCount = get_object_count(OBJECT_CHANNEL_NUMBER);

        if (objectCount <= 0) {
          printf("Object lost.\n");
          ao();
          gv_stateFailedSignal = 1;
          wait_for_milliseconds(1000);
        } else {
          UpdateMotorPowers_TrackObject(&leftMotorPower, &rightMotorPower);
          if (leftMotorPower == 0 && rightMotorPower == 0) {
            // shut off motors.
            ao();

            // command lasso to down state.
            gv_lassoState = LASSO_STATE_DOWN;

            // report to executive and give it time to react.
            printf("Object lassoed.\n");
            gv_stateFinishedSignal = 1;
            wait_for_milliseconds(1000);
          } else {
            demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
          }
        }
        break;
      case ROBOT_STATE_APPROACHING_GOAL:
        break;
      case ROBOT_STATE_PLACING_OBJECT:
        break;
      case ROBOT_STATE_INVALID:
        // Raise error.
        break;
    }
  }
  wait_for_milliseconds(100);
}


void UpdateMotorPowers_TrackObject(int *leftMotorPower, int *rightMotorPower) {
  int objectXLocation = 0;
  int objectYLocation = 0;
  int yPowerComponent = 0;

  objectXLocation = get_object_center_x(OBJECT_CHANNEL_NUMBER, 0);
  objectYLocation = get_object_center_y(OBJECT_CHANNEL_NUMBER, 0);

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
}
