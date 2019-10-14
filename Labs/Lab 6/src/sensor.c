#include "sensor.h"

int NormalizeSensorReading(int sensorValue, int minPossibleValue, int maxPossibleValue) {
    // Apply transform
    int output = 100 - ((sensorValue - maxPossibleValue) * 100) / (minPossibleValue - maxPossibleValue);

    // Return value based on range
    if (output < 0) {
      return 0;
    } else if (output > 100) {
      return 100;
    } else {
      return output;
    }
}
