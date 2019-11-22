#ifndef GLOBALS_H
#define GLOBALS_H

#include "running_average.h"

// Enums
typedef enum {
  ROBOT_STATE_INVALID = 0,
  ROBOT_STATE_READING_QR = 1,
  ROBOT_STATE_SEARCHING_FOR_OBJECT = 2,
  ROBOT_STATE_APPROACHING_OBJECT = 3,
  ROBOT_STATE_APPROACHING_GOAL = 4,
  ROBOT_STATE_PLACING_OBJECT = 5
} ROBOT_STATE;

typedef enum {
  LASSO_STATE_INVALID = 0,
  LASSO_STATE_DOWN = 1,
  LASSO_STATE_UP = 2,
  LASSO_STATE_WAITING = 3
} LASSO_STATE;

// Global variables
extern ROBOT_MODE gv_robotMode;
extern LASSO_STATE gv_lassoState;
extern RunningAverage gv_ra_x;
extern RunningAverage gv_ra_y;
extern int gv_lastObjectX;
extern int gv_lastObjectY;
extern int gv_lastObjectCount;
extern int gv_stateFinishedSignal;
extern int gv_stateFailedSignal;

#endif
