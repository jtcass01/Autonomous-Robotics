#ifndef SENSOR_H
#define SENSOR_H

#include <kipr/botball.h>
#include "constants.h"
#include "globals.h"
#include "utilities.h"

void ReportAnalogSensorValues(int sensorControl);
void ReportCameraPosition(int channelNumber);
void ReportIRSensors(void);
void ReportNormalizedIRSensors(void);
int ConvertFrontSonarReadingToCM(int sensorReading);
int ConvertFrontSonarCMToSonarReading(int distance);
int ConvertLeftLidarReadingToCM(int sensorReading);
int ConvertLeftLidarCMToSonarReading(int distance);

#endif
