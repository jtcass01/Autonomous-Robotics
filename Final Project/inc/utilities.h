#ifndef UTILITIES_H
#define UTILITIES_H

int bind(int value, int min, int max);
void printData(char *dataLabel, int *data, int dataSize);
int NormalizeSensorReading(int sensorValue, int minSensorValue, int maxSensorValue);

#endif
