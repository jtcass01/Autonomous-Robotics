#ifndef ROBOT_H
#define ROBOT_H

#include <kipr/botball.h>
#include "constants.h"
#include "sensor.h"
#include "lasso.h"
#include "globals.h"
#include "move.h"

// Function prototypes
void Demo(void);
void DriveThread(void);
void ButtonThread(void);
int UpdateMotorPowers_TrackObject(int *leftMotorPower, int *rightMotorPower);

#endif
