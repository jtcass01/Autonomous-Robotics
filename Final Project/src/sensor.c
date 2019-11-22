#include "sensor.h"

void ReportAnalogSensorValues(int sensorControl) {
  int ix = 0;
  int sensorResponse = 0;
  int sensorReadings[TEST_DATA_ARRAY_SIZE] = {0};

  while(ix < TEST_DATA_ARRAY_SIZE) {
    sensorResponse = analog(sensorControl);
    sensorReadings[ix++] = sensorResponse;
    printf("Sensor Response for analog pin %d = %d\n", sensorControl, sensorResponse);
    wait_for_milliseconds(100);
  }

  printData("Sensor Readings", sensorReadings, TEST_DATA_ARRAY_SIZE);
}

void ReportCameraPosition(void) {
  int channelNumber = OBJECT_CHANNEL_NUMBER;
  int objectYLocation = 0;
  int objectXLocation = 0;
  int objectCount = 0;
  int ix = 0;
  int xReadings[TEST_DATA_ARRAY_SIZE] = {0};
  int yReadings[TEST_DATA_ARRAY_SIZE] = {0};

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

      printf("Object Location: (%d, %d)\n", xReadings[ix], yReadings[ix]);
      ix++;
    }

    wait_for_milliseconds(100);
  }

  printData("xReadings", xReadings, TEST_DATA_ARRAY_SIZE);
  printData("yReadings", yReadings, TEST_DATA_ARRAY_SIZE);

  //close the connection with the camera.
  camera_close();
}

int ConvertFrontSonarReadingToCM(int sensorReading) {
  int result = (int) (((float) sensorReading - 42.0747619) / 2.96188645)

  if result < 6 {
    return 6;
  } else {
    return result;
  }
}

int ConvertFrontSonarCMToSonarReading(int distance) {
  return (int) (2.96188645 * distance + 42.0747619);
}

int ConvertLeftLidarReadingToCM(int sensorReading) {
  int result = (int) (((float) sensorReading - 3034.46775758) / -70.7440202)

  if result < 10 {
    return 10;
  } else {
    return result;
  }
}

int ConvertLeftLidarCMToSonarReading(int distance) {
  return (int) (-70.7440202 * distance + 3034.46775758);
}
