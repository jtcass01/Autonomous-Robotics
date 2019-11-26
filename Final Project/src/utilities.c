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
    while(dataIndex < dataSize) {
        if(dataIndex < dataSize-1) {
	        printf("%d, ", data[dataIndex]);
        } else {
	        printf("%d", data[dataIndex]);
        }
        dataIndex++;
    }
    printf("]\n");
}

void BubbleSort(int *array, int array_size) {
  int i = 0;
  int j = 0;
  int temp = 0;

  for (i = 0; i < array_size - 1; i++) {
    for (j = 0; j < array_size - i - 1; j++) {
      if (array[j] > array[j+1]) {
        // swap indices
        temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
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
