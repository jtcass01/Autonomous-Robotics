#ifndef CONSTANTS_H
#define CONSTANTS_H

// Camera Constants
#define OBJECT_CHANNEL_NUMBER                 0
#define QR_CHANNEL_NUMBER                     1
#define IMAGE_WIDTH                           160
#define IMAGE_HEIGHT                          120
#define OBJECT_X_GOAL                         80
#define OBJECT_LASSO_Y_CAP                    97
#define OBJECT_LASSO_X_TOLERANCE              2

// Servo Motors
#define LASSO_SERVO                           0
#define LASSO_DOWN_ENCODER                    400
#define LASSO_UP_ENCODER                      1550

// Motors
#define LEFT_MOTOR                            0
#define RIGHT_MOTOR                           1

// Analog Inputs
/// Front Sonar
#define A_FRONT_SONAR                         0
#define A_FRONT_SONAR_MAX                     4092
#define A_FRONT_SONAR_MIN                     0
#define A_FRONT_SONAR_COLLISION_THRESHOLD_CM  15
/// Left Lidar
#define A_LEFT_LIDAR                          1
#define A_LEFT_LIDAR_MAX                      4092
#define A_LEFT_LIDAR_MIN                      0
#define A_LEFT_LIDAR_WALL_FOLLOW_GOAL_CM      16
/// Front Left
#define A_FRONT_LEFT_IR                       2
#define A_FRONT_LEFT_IR_MAX                   4092
#define A_FRONT_LEFT_IR_MIN                   0
/// Front Right
#define A_FRONT_RIGHT_IR                      3
#define A_FRONT_RIGHT_IR_MAX                  4092
#define A_FRONT_RIGHT_IR_MIN                  0
/// Back Left
#define A_BACK_LEFT_IR                        4
#define A_BACK_LEFT_IR_MAX                    4092
#define A_BACK_LEFT_IR_MIN                    0
/// Back Right
#define A_BACK_RIGHT_IR                       5
#define A_BACK_RIGHT_IR_MAX                   4092
#define A_BACK_RIGHT_IR_MIN                   0

// PID Controller Constants
#define PID_WALL_FOLLOW_KP                    0.01
#define PID_WALL_FOLLOW_KI                    0
#define PID_WALL_FOLLOW_KD                    0

// Testing Constants
#define TEST_DATA_ARRAY_SIZE		              151

#endif
