#ifndef GLOBALS_H
#define GLOBALS_H

// Enums
typedef enum {
  ROBOT_STATE_INVALID = 0,
  ROBOT_STATE_READING_QR = 1,
  ROBOT_STATE_SEARCHING_FOR_OBJECT = 2,
  ROBOT_STATE_APPROACHING_OBJECT = 3,
  ROBOT_STATE_APPROACHING_GOAL = 4,
  ROBOT_STATE_LEAVING_BASE = 5
} ROBOT_STATE;


typedef enum {
  LASSO_STATE_INVALID = 0,
  LASSO_STATE_DOWN = 1,
  LASSO_STATE_UP = 2,
} LASSO_STATE;

typedef enum {
  OBJECT_COLOR_INVALID = 0,
  OBJECT_COLOR_GREEN = 1,
  OBJECT_COLOR_ORANGE = 2,
  OBJECT_COLOR_PURPLE = 3,
} OBJECT_COLOR;

typedef enum {
  HOME_BASE_INVALID = 0,
  HOME_BASE_WHITE = 1,
  HOME_BASE_BLACK = 2
} HOME_BASE;

// Global variables
extern ROBOT_STATE gv_robotState;
extern LASSO_STATE gv_lassoState;
extern OBJECT_COLOR gv_objectColor;
extern HOME_BASE gv_homeBase;
extern int gv_dealingWithFrontButton;
extern int gv_dealingWithBackButton;

#endif
