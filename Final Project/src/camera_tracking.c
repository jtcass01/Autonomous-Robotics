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
