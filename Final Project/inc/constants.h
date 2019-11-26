#ifndef CONSTANTS_H
#define CONSTANTS_H

// Camera Constants
#define GREEN_CHANNEL_NUMBER                  1
#define ORANGE_CHANNEL_NUMBER                 2
#define PURPLE_CHANNEL_NUMBER                 3
#define QR_CHANNEL_NUMBER                     0
#define IMAGE_WIDTH                           160
#define IMAGE_HEIGHT                          120
#define OBJECT_X_GOAL                         80
#define OBJECT_LASSO_Y_CAP                    100
#define OBJECT_LASSO_X_TOLERANCE              2

// Servo Motors
#define LASSO_SERVO                           0
#define LASSO_DOWN_ENCODER                    500
#define LASSO_UP_ENCODER                      1550
#define LASSO_START_ENCODER					          600

// Motors
#define LEFT_MOTOR                            0
#define RIGHT_MOTOR                           1

/// Front IR
#define A_FRONT_IR                        0
#define A_FRONT_IR_WHITE_MIN              286
#define A_FRONT_IR_WHITE_MAX              2828
#define A_FRONT_IR_BLACK_MIN              155
#define A_FRONT_IR_BLACK_MAX              215
#define NUM_IR_SPIN_READINGS              50

// Digital Inputs
#define D_BACK_BUTTON                         0
#define D_FRONT_LEFT_BUTTON                   1
#define D_FRONT_RIGHT_BUTTON                  2

// Testing Constants
#define TEST_DATA_ARRAY_SIZE		              151

#endif
