#include "utilities.h"

int bind(int value, int lowerBound, int upperBound) {
  if (value < lowerBound) {
    return lowerBound;
  } else if (value > upperBound) {
    return upperBound;
  } else {
    return value;
  }
}


void printData(char *dataLabel, int *data, int dataSize) {
    printf("%s : [", dataLabel);
    int dataIndex = 0;
    while(++dataIndex < dataSize) {
        if(dataIndex < dataSize) {
	        printf("%d, ", data[dataIndex]);
        } else {
	        printf("%d", data[dataIndex]);
        }
    }
    printf("]\n");
}

int NormalizeSensorReading(int sensorValue, int minSensorValue, int maxSensorValue) {
    // Apply transform
    int output = 100 - ((sensorValue - maxSensorValue) * 100) / (minSensorValue - maxSensorValue);

    // Return value based on range
    if (output < 0) {
      return 0;
    } else if (output > 100) {
      return 100;
    } else {
      return output;
    }
}
