#ifndef SENSOR_H
#define SENSOR_H

#include <kipr/botball.h>
#include "constants.h"
#include "utilities.h"

void ReportAnalogSensorValues(int sensorControl);
void ReportCameraPosition(void);
int ConvertFrontSonarReadingToCM(int sensorReading);
int ConvertFrontSonarCMToSonarReading(int distance);
int ConvertLeftLidarReadingToCM(int sensorReading);
int ConvertLeftLidarCMToSonarReading(int distance);

#endif
