#include "camera_tracking.h"

void ObjectLocalizationThread(void) {
  // Global variables
  extern int gv_lastObjectCount;
  extern int gv_lastObjectX;
  extern int gv_lastObjectY;
  extern RunningAverage gv_ra_x;
  extern RunningAverage gv_ra_y;

  int objectXLocation = 0;
  int objectYLocation = 0;
  int channelNumber = OBJECT_CHANNEL_NUMBER;

  // Open a connection with the camera.
  camera_open();

  while(1) {
    camera_update();

    // Get object count
    gv_lastObjectCount = get_object_count(channelNumber);

    if (gv_lastObjectCount > 0) {
      // Assume we are tracking the largest object
      objectXLocation = get_object_center_x(channelNumber, 0);
      objectYLocation = get_object_center_y(channelNumber, 0);

      gv_lastObjectX = RA_Update(&gv_ra_x, objectXLocation);
      gv_lastObjectY = RA_Update(&gv_ra_y, objectYLocation);
    } else {
      // Reinitialize running averages if object is lost.
      RA_Init(&gv_ra_x);
      RA_Init(&gv_ra_y);
    }

    wait_for_milliseconds(100);
  }

  //close the connection with the camera.
  camera_close();
}

void ReportCameraPosition(void) {
  int channelNumber = OBJECT_CHANNEL_NUMBER;
  int objectYLocation = 0;
  int objectXLocation = 0;
  int objectCount = 0;
  int ix = 0;
  int xReadings[TEST_DATA_ARRAY_SIZE] = {0};
  int yReadings[TEST_DATA_ARRAY_SIZE] = {0};
  int xRAReadings[TEST_DATA_ARRAY_SIZE] = {0};
  int yRAReadings[TEST_DATA_ARRAY_SIZE] = {0};
  RunningAverage xRA = {0};
  RunningAverage yRA = {0};

  // Initialize Running Averages
  RA_Init(&xRA);
  RA_Init(&yRA);

  // Open a connection with the camera.
  camera_open();

  while(ix < TEST_DATA_ARRAY_SIZE) {
    // Update the camera image
    camera_update();

    // Get object count
    objectCount = get_object_count(channelNumber);

    if (objectCount > 0) {
      // Assume we are tracking the largest object
      objectXLocation = get_object_center_x(channelNumber, 0);
      objectYLocation = get_object_center_y(channelNumber, 0);
      xReadings[ix] = objectXLocation;
      yReadings[ix] = objectYLocation;
      xRAReadings[ix] = RA_Update(&xRA, objectXLocation);
      yRAReadings[ix] = RA_Update(&yRA, objectYLocation);

      printf("Object Location: (%d, %d)\n", xRAReadings[ix], yRAReadings[ix]);
      ix++;
    } else {
      RA_Init(&xRA);
      RA_Init(&yRA);
    }

    wait_for_milliseconds(100);
  }

  printData("xReadings", xReadings, TEST_DATA_ARRAY_SIZE);
  printData("xRAReadings", xRAReadings, TEST_DATA_ARRAY_SIZE);
  printData("yReadings", yReadings, TEST_DATA_ARRAY_SIZE);
  printData("yRAReadings", yRAReadings, TEST_DATA_ARRAY_SIZE);

  //close the connection with the camera.
  camera_close();
}
