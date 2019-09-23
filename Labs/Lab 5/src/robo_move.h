
#ifndef ROBO_MOVE_H
#define ROBO_MOVE_H

#include <kipr/botball.h>

void goDemobot(int leftMotor, int rightMotor, int millisecond_t, int powerLevel_l, int powerLevel_r); // function prototype
void goDemobotMav(int leftMotor, int rightMotor, int millisecond_t, int leftVelocity, int rightVelocity);
void goStraight(int leftMotor, int rightMotor, int millisecond_t, int powerLevel);
void goStraightMrp(int leftMotor, int rightMotor, int velocity, int numberOfTicks);
void goStraightMav(int leftMotor, int rightMotor, int millisecond_t, int velocity);
void make90Turn(int leftMotor, int rightMotor, int leftTurn, int powerLevel);
void turnLeft(int leftMotor, int rightMotor);
void turnRight(int leftMotor, int rightMotor);
void driftLeftMav(int leftMotor, int rightMotor, int millisecond_t, int velocity);
void driftRightMav(int leftMotor, int rightMotor, int millisecond_t, int velocity);
void makeCircle(int leftMotor, int rightMotor);
void figureEight(int leftMotor, int rightMotor);

#endif
