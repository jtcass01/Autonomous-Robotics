#include "robo_move.h"
#include "sensor.h"

#define SONAR_SENSOR 2
#define CHANNEL_NUMBER 0
#define IMAGE_WIDTH 160
#define IMAGE_HEIGHT 120
#define LEFT_MOTOR 0
#define RIGHT_MOTOR 1

void RotationalTracking(void);
void TranslationalTracking(void);
void RotationalAndTranslationalTracking(void);
void ObstacleAvoidanceWhileTracking(void);
void SonarObstacleAvoidanceThread(void);
void RotationalAndTranslationalTrackingThread(void);
int bind(int value, int lowerBound, int upperBound);
void ReportSonarDistance();
float ConvertSonarToDistance(int analogResponse);

int gv_sonarEvent;
int gv_lastX;
int gv_lastY;

int main() {
    gv_sonarEvent = 0;
    gv_lastX = 0;
    gv_lastY= 0;
    ObstacleAvoidanceWhileTracking();
    return 0;
}

void ObstacleAvoidanceWhileTracking(void) {
    // create threads
    thread sonarThread = thread_create(SonarObstacleAvoidanceThread);
    thread cameraThread = thread_create(RotationalAndTranslationalTrackingThread);

    // start threads
    thread_start(sonarThread);
    thread_start(cameraThread);

    // Run for 5 minutes
    wait_for_milliseconds(60000 * 5);

    // Destroy threads
    thread_destroy(sonarThread);
    thread_destroy(cameraThread);
}

void SonarObstacleAvoidanceThread(void) {
    int sonarAnalogReading = 0;
    float sensorDistance = 0;
    int sonarThreshold = 20;
    
    while(1) {
        // Get sensor reading
        sonarAnalogReading = analog(SONAR_SENSOR);
        
        sensorDistance = ConvertSonarToDistance(sonarAnalogReading);
        
        if (sensorDistance < sonarThreshold) {
            ao();
            gv_sonarEvent = 1;
            printf("\nSonar Event is occuring!");
            
            if(gv_lastX < IMAGE_WIDTH / 2) {
              // Back up
              goStraightMav(LEFT_MOTOR, RIGHT_MOTOR, 2000, -500);
              // Turn left
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1800, 0, 1000);
              // Go straight
              goStraightMav(LEFT_MOTOR, RIGHT_MOTOR, 2500, 500);
              // Turn Right 90
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1800, 1000, 0);
            } else {
              // Back up
              goStraightMav(LEFT_MOTOR, RIGHT_MOTOR, 2000, -500);
              // Turn Right 90
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1800, 1000, 0);
              // Go straight
              goStraightMav(LEFT_MOTOR, RIGHT_MOTOR, 2500, 500);
              // Turn left
              goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 1800, 0, 1000);
            }
            
            gv_sonarEvent = 0;
        }
    }
}

void RotationalAndTranslationalTrackingThread(void) {
    int imageHalfHeight = IMAGE_HEIGHT / 2;
    int objectYLocation = imageHalfHeight;
    int imageHalfWidth = IMAGE_WIDTH / 2;
    int objectXLocation = imageHalfWidth;
    int objectCount = 0;
    int rotationalTolerance = 20;
    int translationalTolerance = 8;
    int leftMotorPower = 0;
    int rightMotorPower = 0;
    
    // Open a connection with the camera.
    camera_open();
    
    while(1) {
        while(!gv_sonarEvent) {
            // Update the camera image
            camera_update();

            // Get the object count
            objectCount = get_object_count(CHANNEL_NUMBER);

            if (objectCount > 0) {
                // Assume we are tracking the largest object
                objectXLocation = get_object_center_x(CHANNEL_NUMBER, 0);
                objectYLocation = get_object_center_y(CHANNEL_NUMBER, 0);
                gv_lastX = objectXLocation;
                gv_lastY = objectYLocation;

                // Check if the objectYLocation is outside of the tolerance
                if ( objectYLocation < imageHalfHeight - translationalTolerance || objectYLocation > imageHalfHeight + translationalTolerance ) {
                    if (objectYLocation < imageHalfHeight) {
                        // Object is too far away
                        leftMotorPower += 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                        rightMotorPower += 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                    } else {
                        // Object is too close
                        leftMotorPower += -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                        rightMotorPower += -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                    }
                }

                leftMotorPower /= 2;
                rightMotorPower /= 2;

                // Check if the objectXLocation is outside of the tolerance
                if ( objectXLocation < imageHalfWidth - rotationalTolerance || objectXLocation > imageHalfWidth + rotationalTolerance ) {
                    if (objectXLocation < imageHalfWidth) {
                        // Object is to the left.
                        rightMotorPower += 100 - NormalizeSensorReading(objectXLocation, 0, imageHalfWidth) - 50;
                    } else {
                        // Object is to the right.
                        leftMotorPower += NormalizeSensorReading(objectXLocation, imageHalfWidth, IMAGE_WIDTH) - 50;
                    }
                }

                // Move motor appropriately.
                if (leftMotorPower == 0 && rightMotorPower == 0) {
                    ao();
                } else {
                    leftMotorPower = bind(leftMotorPower, -100, 100);
                    rightMotorPower = bind(rightMotorPower, -100, 100);

                    demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
                }

            } else {
                ao();
                if(gv_lastX < IMAGE_WIDTH / 2) {
                    // Pan to the left looking for the object.
                    goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 600, 0, 1000);
                } else {
                    // Pan to the right looking for the object.
                    goDemobotMav(LEFT_MOTOR, RIGHT_MOTOR, 600, 1000, 0);
                }
            }
        }
        wait_for_milliseconds(100);
    }
    
    //close the connection with the camera.
    camera_close();
}


void RotationalAndTranslationalTracking(void) {
    int imageHalfHeight = IMAGE_HEIGHT / 2;
    int objectYLocation = imageHalfHeight;
    int imageHalfWidth = IMAGE_WIDTH / 2;
    int objectXLocation = imageHalfWidth;
    int objectCount = 0;
    int rotationalTolerance = 20;
    int translationalTolerance = 8;
    int leftMotorPower = 0;
    int rightMotorPower = 0;
    
    // Open a connection with the camera.
    camera_open();
    
    while(1) {
        // Update the camera image
        camera_update();
        
        // Get the object count
        objectCount = get_object_count(CHANNEL_NUMBER);
        
        if (objectCount > 0) {
            // Assume we are tracking the largest object
            objectXLocation = get_object_center_x(CHANNEL_NUMBER, 0);
            objectYLocation = get_object_center_y(CHANNEL_NUMBER, 0);
            printf("\nThe object's x location is %d", objectXLocation);
            printf("\nThe object's y location is %d", objectYLocation);
            
            // Check if the objectYLocation is outside of the tolerance
            if ( objectYLocation < imageHalfHeight - translationalTolerance || objectYLocation > imageHalfHeight + translationalTolerance ) {
                if (objectYLocation < imageHalfHeight) {
                    // Object is too far away
                    leftMotorPower += 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                    rightMotorPower += 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                } else {
                    // Object is too close
                    leftMotorPower += -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                    rightMotorPower += -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                }
            }

            printf("\nY Power component is %d", leftMotorPower);
            leftMotorPower /= 2;
            rightMotorPower /= 2;


            // Check if the objectXLocation is outside of the tolerance
            if ( objectXLocation < imageHalfWidth - rotationalTolerance || objectXLocation > imageHalfWidth + rotationalTolerance ) {
                if (objectXLocation < imageHalfWidth) {
                    // Object is to the left.
                    rightMotorPower += 100 - NormalizeSensorReading(objectXLocation, 0, imageHalfWidth) - 50;
                } else {
                    // Object is to the right.
                    leftMotorPower += NormalizeSensorReading(objectXLocation, imageHalfWidth, IMAGE_WIDTH) - 50;
                }
            }

            // Move motor appropriately.
            if (leftMotorPower == 0 && rightMotorPower == 0) {
                ao();
            } else {
                printf("\nleftMotorPower before bind %d", leftMotorPower);
                printf("\nrightMotorPower before bind %d", rightMotorPower);
                leftMotorPower = bind(leftMotorPower, -100, 100);
                rightMotorPower = bind(rightMotorPower, -100, 100);
                printf("\nleftMotorPower after bind %d", leftMotorPower);
                printf("\nrightMotorPower after bind %d", rightMotorPower);
                
            	demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
            }
            
        } else {
            ao();
        }
    }
    
    //close the connection with the camera.
    camera_close();
}


void TranslationalTracking(void) {
    int imageHalfHeight = IMAGE_HEIGHT / 2;
    int objectYLocation = imageHalfHeight;
    int objectCount = 0;
    int tolerance = 3;
    int leftMotorPower = 0;
    int rightMotorPower = 0;
    
    // Open a connection with the camera.
    camera_open();

    while(1) {
        // Update the camera image
        camera_update();
        
        // Get the object count
        objectCount = get_object_count(CHANNEL_NUMBER);
        
        if (objectCount > 0) {
            // Assume we are tracking the largest object
            objectYLocation = get_object_center_y(CHANNEL_NUMBER, 0);
            printf("\nThe object's y location is %d", objectYLocation);
            
            // Check if the objectYLocation is outside of the tolerance
            if ( objectYLocation < imageHalfHeight - tolerance || objectYLocation > imageHalfHeight + tolerance ) {
                if (objectYLocation < imageHalfHeight) {
                    // Object is too far away
                    leftMotorPower = 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                    rightMotorPower = 100 - NormalizeSensorReading(objectYLocation, 0, imageHalfHeight);
                } else {
                    // Object is too close
                    leftMotorPower = -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                    rightMotorPower = -1 * NormalizeSensorReading(objectYLocation, imageHalfHeight, IMAGE_HEIGHT);
                }
                demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
            } else {
                ao();
            }
        } else {
            ao();
        }
    }
    
    //close the connection with the camera.
    camera_close();
}

void RotationalTracking(void) {
    int imageHalfWidth = IMAGE_WIDTH / 2;
    int objectXLocation = imageHalfWidth;
    int objectCount = 0;
    int tolerance = 20;
    int leftMotorPower = 0;
    int rightMotorPower = 0;

    // Open a connection with the camera.
    camera_open();

    while(1) {
        // Update the camera image
        camera_update();
        
        // Get the object count
        objectCount = get_object_count(CHANNEL_NUMBER);
        
        if (objectCount > 0) {
            // Assume we are tracking the largest object
            objectXLocation = get_object_center_x(CHANNEL_NUMBER, 0);
            printf("\nThe object's x location is %d", objectXLocation);
            
            // Check if the objectXLocation is outside of the tolerance
            if ( objectXLocation < imageHalfWidth - tolerance || objectXLocation > imageHalfWidth + tolerance ) {
                if (objectXLocation < imageHalfWidth) {
                    // Object is to the left.
                    leftMotorPower = 0;
                    rightMotorPower = 100 - NormalizeSensorReading(objectXLocation, 0, imageHalfWidth);
                } else {
                    // Object is to the right.
                    leftMotorPower = NormalizeSensorReading(objectXLocation, imageHalfWidth, IMAGE_WIDTH);
                    rightMotorPower = 0;
                }
                demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);
            } else {
                ao();
            }
        } else {
            ao();
        }
    }
    
    //close the connection with the camera.
    camera_close();
}


int bind(int value, int lowerBound, int upperBound) {
  if (value < lowerBound) {
    return lowerBound;
  } else if (value > upperBound) {
    return upperBound;
  } else {
    return value;
  }
}


float ConvertSonarToDistance(int analogResponse) {
    if(analogResponse < 52) {
        analogResponse = 52;
    } else if (analogResponse > 2000) {
        analogResponse = 2000;
    }
    
    return ((float) analogResponse - 4.81585) / 3.04371;
}

void ReportSonarDistance() {
    int sonarAnalogReading = 0;
    float sensorDistance = 0;
    
    while(1) {
        // Get sensor reading
        sonarAnalogReading = analog(SONAR_SENSOR);
        
        sensorDistance = ConvertSonarToDistance(sonarAnalogReading);
        
        printf("Distance is %f cm.\n", sensorDistance);
    }
}
