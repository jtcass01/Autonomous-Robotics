#include <kipr/botball.h>

void goDemobot(int millisecond_t, int powerLevel_l, int powerLevel_r); // function prototype
void goStraight(int millisecond_t, int powerLevel);
void goStraightMrp(int velocity, int numberOfTicks);
void goStraightMav(int millisecond_t, int velocity);
void make90Turn(int leftTurn, int powerLevel);
void turnLeft();
void turnRight();
void makeCircle();
void figureEight();
void four_by_four_feet_mav();
void four_by_four_feet_mrp();
void walkAndDisplayDistance(int);

int main() {
    four_by_four_feet_mrp();
    return 0;
} // end main

void goDemobot(int millisecond_t, int powerLevelLeft, int powerLevelRight) {
    int LeftMotor = 0; /* Left motor is connected to port 3 */
    int RightMotor = 3; /* Right motor is connected to port 0 */
    motor(LeftMotor, powerLevelLeft * 0.925);
    motor(RightMotor, powerLevelRight);
    wait_for_milliseconds(millisecond_t);
    ao();
}
// end goDemobot

void goStraight(int millisecond_t, int powerLevel) {
    goDemobot(millisecond_t, powerLevel, powerLevel);
}

void goStraightMrp(int velocity, int numberOfTicks) {
    mrp(0, velocity*0.944, numberOfTicks);
    mrp(3, velocity, numberOfTicks);
    msleep(velocity*numberOfTicks);
}


void goStraightMav(int millisecond_t, int velocity) {
    mav(0, velocity*0.944);
    mav(3, velocity);
    msleep(millisecond_t);
    ao();
}


void make90Turn(int leftTurn, int powerLevel) {
    if(leftTurn) {
        /// Turn 90 degress Left
        goDemobot(2000 , 0, powerLevel);
    } else {
	    /// Turn 90 degrees Right
        goDemobot(2000, powerLevel, 0);
    }
}

void turnLeft() {
    // Turn left
	make90Turn(1, 63);
}

void turnRight() {
    // Turn right
	make90Turn(0, 63);
}

void four_by_four_box() {
    goStraight(680, 100); // function call
    turnRight();
    goStraight(680, 100); // function call
    turnRight();
    goStraight(680, 100); // function call
    turnRight();
    goStraight(680, 100); // function call
    turnRight();
}


void two_by_two_box() {
    goStraight(680, 50); // function call
    turnRight();
    goStraight(680, 50); // function call
    turnRight();
    goStraight(680, 50); // function call
    turnRight();
    goStraight(680, 50); // function call
    turnRight();
}

void makeCircle() {
    goDemobot(10370, 60, 10);
}

void figureEight() {
    goDemobot(5185, 60, 10);
    goDemobot(10170, 10, 60);
    goDemobot(5185, 60, 10);
}

void four_by_four_feet_mav() {
    goStraightMav(22000, 500);
    turnRight();
    goStraightMav(22000, 500);
    turnRight();
    goStraightMav(22000, 500);
    turnRight();
    goStraightMav(22000, 500);
    turnRight();
}

void four_by_four_feet_mrp() {
    goStraightMrp(1000, 15000);
    turnRight();
    goStraightMrp(1000, 15000);
    turnRight();
    goStraightMrp(1000, 15000);
    turnRight();
    goStraightMrp(1000, 15000);
    turnRight();
}


void walkAndDisplayDistance(int timeRunning) {
    float startTime = seconds();
    float runTime = 0;
    float distanceTraveled = 0;

    while((runTime*1000)  < timeRunning) {
	    goStraight(1000, 50); // function call
        runTime = seconds() - startTime;
        distanceTraveled = runTime * 3;
        printf("Runtime: %0.2f | Distance Traveled: %0.2f\n", runTime, distanceTraveled);
    }
}
