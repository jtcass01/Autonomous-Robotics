#ifndef UTILITIES_H
#define UTILITIES_H

#include <kipr/botball.h>

int bind(int value, int min, int max);
void printData(char *dataLabel, int *data, int dataSize);
int NormalizeSensorReading(int sensorValue, int minSensorValue, int maxSensorValue);
void BubbleSort(int *array, int array_size);

#endif
