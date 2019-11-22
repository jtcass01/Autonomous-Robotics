#ifndef ROBOT_H
#define ROBOT_H

#include <kipr/botball.h>
#include "constants.h"
#include "sensor.h"
#include "lasso.h"
#include "globals.h"

// Function prototypes
void Demo(void);
void ExecutiveThread(void);
void DriveThread(void);
void UpdateMotorPowers_TrackObject(int *leftMotorPower, int *rightMotorPower);

#endif
