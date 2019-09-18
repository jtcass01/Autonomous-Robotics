#include <kipr/botball.h>
#include "robo_move.h"

void senseLight();
void feelObjects();
void metaSensing();
void randomSeekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor,
                     int leftTouchSensor, int rightTouchSensor);
void getOutOfJar(int leftMotor, int rightMotor);
void seekLightAndAvoidObstacles(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor,
                                int leftTouchSensor, int rightTouchSensor);
void seekDarkness(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor);
void seekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor);
int NormalizeLightReadings(int lightValue, int minLightValue, int maxLightValue);
void displayAnalogReadings(int lightSensor1, int lightSensor2);

#define MINLEFTLIGHTREADING 260
#define MAXLEFTLIGHTREADING 4050
#define MINRIGHTLIGHTREADING 236
#define MAXRIGHTLIGHTREADING 4080
#define MINAMBIENTLIGHTREADING 220
#define MAXAMBIENTLIGHTREADING 4036
#define SPEEDFACTOR 50

int dealingWithTouchSensor;


int main() {
    int leftMotor = 0;
    int rightMotor = 3;
    int leftIRSensorLocation = 0;
    int rightIRSensorLocation = 1;
    int leftTouchSensor = 0;
    int rightTouchSensor = 1;
    int leftLightSensor = 2;
    int ambientLightSensor = 3;
    int rightLightSensor = 4;
    dealingWithTouchSensor = 0;

    seekLightAndAvoidObstacles(leftMotor, rightMotor, leftLightSensor, rightLightSensor, ambientLightSensor, leftTouchSensor, rightTouchSensor);

    return 0;
}


void displayAnalogReadings(int lightSensor1, int lightSensor2) {
    int lightSensor1Reading = 0;
    int lightSensor2Reading = 0;

    while(1) {
      lightSensor1Reading = analog(lightSensor1);
      lightSensor2Reading = analog(lightSensor2);
      printf("Sensor 1 [%d]: %d | Sensor 2 [%d]: %d\n", lightSensor1, lightSensor1Reading, lightSensor2, lightSensor2Reading);
      wait_for_milliseconds(1000);
    }
}


int NormalizeLightReadings(int lightValue, int minLightValue, int maxLightValue) {
    // Apply transform
    int output = 100 - ((lightValue - maxLightValue) * 100) / (minLightValue - maxLightValue);

    // Return value based on range
    if (output < 0) {
      return 0;
    } else if (output > 100) {
      return 100;
    } else {
      return output;
    }
}


void seekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor) {
  // Initialize variables
  int leftSensorReading = 0;
  int rightSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), MINLEFTLIGHTREADING, MAXLEFTLIGHTREADING);
    rightSensorReading = NormalizeLightReadings(analog(rightLightSensor), MINRIGHTLIGHTREADING, MAXRIGHTLIGHTREADING);
    // Subtract ambient light sensor value
    leftSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
    rightSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
    printf("Left Light Sensor : %d | Right Light Sensor 2 : %d\n", leftSensorReading, rightSensorReading);

    // Move demobot in response to the sensor values
    goDemobotMav(leftMotor, rightMotor, 10, leftSensorReading*SPEEDFACTOR, rightSensorReading*SPEEDFACTOR);
  }
}


void seekDarkness(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftSensorReading = 100 - NormalizeLightReadings(analog(leftLightSensor), MINLEFTLIGHTREADING, MAXLEFTLIGHTREADING);
    rightSensorReading = 100 - NormalizeLightReadings(analog(rightLightSensor), MINRIGHTLIGHTREADING, MAXRIGHTLIGHTREADING);
    // Subtract ambient light sensor value
    leftSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
    rightSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);

    goDemobotMav(leftMotor, rightMotor, 10, leftSensorReading*SPEEDFACTOR, rightSensorReading*SPEEDFACTOR);
  }
}


void seekLightAndAvoidObstacles(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor,
                                int leftTouchSensor, int rightTouchSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;
  int leftTouchSensorReading = 0;
  int rightTouchSensorReading = 0;

  while(1) {
    // get reading from sensors
    leftTouchSensorReading = digital(leftTouchSensor);
    rightTouchSensorReading = digital(rightTouchSensor);
    leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), MINLEFTLIGHTREADING, MAXLEFTLIGHTREADING);
    rightSensorReading = NormalizeLightReadings(analog(rightLightSensor), MINRIGHTLIGHTREADING, MAXRIGHTLIGHTREADING);
    // Subtract ambient light sensor value
    leftSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
    rightSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);

    if(leftTouchSensorReading) {
      // Back up
      goStraightMav(leftMotor, rightMotor, 1000, -500);
      // Turn Right 90
      turnRight(leftMotor, rightMotor);
      // Go straight
      goStraightMav(leftMotor, rightMotor, 500, 500);
      // Turn left
      turnLeft(leftMotor, rightMotor);
    } else if (rightTouchSensorReading) {
      // Back up
      goStraightMav(leftMotor, rightMotor, 1000, -500);
      // Turn left 90
      turnLeft(leftMotor, rightMotor);
      // Go straight
      goStraightMav(leftMotor, rightMotor, 500, 500);
      // Back up
      turnRight(leftMotor, rightMotor);
    } else {
      // Go straight
      goDemobotMav(leftMotor, rightMotor, 50, leftSensorReading*SPEEDFACTOR, rightSensorReading*SPEEDFACTOR);
    }
  }
}


void getOutOfJar(int leftMotor, int rightMotor) {
  goStraightMav(leftMotor, rightMotor, 0, random(1000));
}


void randomSeekLight(int leftMotor, int rightMotor, int leftLightSensor, int rightLightSensor, int ambientLightSensor,
                     int leftTouchSensor, int rightTouchSensor) {
  int leftSensorReading = 0;
  int rightSensorReading = 0;
  int leftTouchSensorReading = 0;
  int rightTouchSensorReading = 0;
  int leftTouchPrevious = 0;
  int rightTouchPrevious = 0;

  while(1) {
    // get reading from sensors
    leftTouchSensorReading = digital(leftTouchSensor);
    rightTouchSensorReading = digital(rightTouchSensor);
    leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), MINLEFTLIGHTREADING, MAXLEFTLIGHTREADING);
    rightSensorReading = NormalizeLightReadings(analog(rightLightSensor), MINRIGHTLIGHTREADING, MAXRIGHTLIGHTREADING);
    // Subtract ambient light sensor value
    leftSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
    rightSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);

    if(leftTouchSensorReading) {
      // Back up
      goStraightMav(leftMotor, rightMotor, 1000, -500);
      // Turn Right 90
      turnRight(leftMotor, rightMotor);
      // Go straight
      goStraightMav(leftMotor, rightMotor, 500, 500);
      // Turn left
      turnLeft(leftMotor, rightMotor);

      // If leftTouchSensor has not recently been touched.
      if (!leftTouchPrevious) {
        // Left touch is now denoted as previous.  Right is enforced not to be previous.
        leftTouchPrevious = 1;
        rightTouchPrevious = 0;
      } else {
        // If the leftTouchSensor has previously been touched, get out of jar.
	      getOutOfJar(leftMotor, rightMotor);
        leftTouchPrevious = 0;
      }
    } else if (rightTouchSensorReading) {
      // Back up
      goStraightMav(leftMotor, rightMotor, 1000, -500);
      // Turn left 90
      turnLeft(leftMotor, rightMotor);
      // Go straight
      goStraightMav(leftMotor, rightMotor, 500, 500);
      // Back up
      turnRight(leftMotor, rightMotor);

      // If rightTouchSensor has not recently been touched.
      if (!rightTouchPrevious) {
        // Right touch is now denoted as previous.  Left is enforced not to be previous.
        rightTouchPrevious = 1;
        leftTouchPrevious = 0;
      } else {
        // If the rightTouchSensor has previously been touched, get out of jar.
        getOutOfJar(leftMotor, rightMotor);
        rightTouchPrevious = 0;
      }
    } else {
      // Move towards light
      goDemobotMav(leftMotor, rightMotor, 50, leftSensorReading*SPEEDFACTOR, rightSensorReading*SPEEDFACTOR);
    }
  }
}


void metaSensing() {
    // create threads
    lightThread = thread_create(senseLight);
    touchThread = thread_create(feelObjects);

    // start threads
    thread_start(lightThread);
    thread_start(touchThread);

    // Run for 5 minutes
    wait_for_milliseconds(60000 * 5);

    // Destroy threads
    thread_destroy(lightThread);
    thread_destroy(touchThread);
}


void senseLight() {
    int leftLightSensor = 2;
    int ambientLightSensor = 3;
    int rightLightSensor = 4;
    int leftSensorReading = 0;
    int rightSensorReading = 0;

    while(1) {
        // WHile not dealing with any touch sensors. dealingWithTouchSensor is a global variable.
        while(!dealingWithTouchSensor) {
            // get sensor readings
            leftSensorReading = NormalizeLightReadings(analog(leftLightSensor), MINLEFTLIGHTREADING, MAXLEFTLIGHTREADING);
            rightSensorReading = NormalizeLightReadings(analog(rightLightSensor), MINRIGHTLIGHTREADING, MAXRIGHTLIGHTREADING);
            // Subtract ambient light sensor value
            leftSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);
            rightSensorReading -= NormalizeLightReadings(analog(ambientLightSensor), MINAMBIENTLIGHTREADING, MAXAMBIENTLIGHTREADING);

            // Move towards light
		        goDemobotMav(leftMotor, rightMotor, 10, leftSensorReading*SPEEDFACTOR, rightSensorReading*SPEEDFACTOR);
        }
    }
}

void feelObjects() {
    int leftTouchSensor = 0;
    int rightTouchSensor = 1;
    int leftTouchSensorReading = 0;
    int rightTouchSensorReading = 0;

    while(1) {
        // Get sensor readings
        leftTouchSensorReading = digital(leftTouchSensor);
        rightTouchSensorReading = digital(rightTouchSensor);

        if(leftTouchSensorReading) {
          dealingWithTouchSensor = 1;
          // Back up
          goStraightMav(leftMotor, rightMotor, 1000, -500);
          // Turn Right 90
          turnRight(leftMotor, rightMotor);
          // Go straight
          goStraightMav(leftMotor, rightMotor, 500, 500);
          // Turn left
          turnLeft(leftMotor, rightMotor);
          dealingWithTouchSensor = 0;
        } else if (rightTouchSensorReading) {
          dealingWithTouchSensor = 1;
          // Back up
          goStraightMav(leftMotor, rightMotor, 1000, -500);
          // Turn left 90
          turnLeft(leftMotor, rightMotor);
          // Go straight
          goStraightMav(leftMotor, rightMotor, 500, 500);
          // Back up
          turnRight(leftMotor, rightMotor);
          dealingWithTouchSensor = 0;
        }
    }
}
