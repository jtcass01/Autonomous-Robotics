#include "utilities.h"

int bind(int value, int lowerBound, int upperBound) {
  if (value < lowerBound) {
    return lowerBound;
  } else if (value > upperBound) {
    return upperBound;
  } else {
    return value;
  }
}


void printData(char *dataLabel, int *data, int dataSize) {
    printf("%s : [", dataLabel);
    int dataIndex = 0;
    while(++dataIndex < dataSize) {
        if(dataIndex < dataSize) {
	        printf("%d, ", data[dataIndex]);
        } else {
	        printf("%d", data[dataIndex]);
        }
    }
    printf("]\n");
}

int NormalizeSensorReading(int sensorValue, int minSensorValue, int maxSensorValue) {
    // Apply transform
    int output = 100 - ((sensorValue - maxSensorValue) * 100) / (minSensorValue - maxSensorValue);

    // Return value based on range
    if (output < 0) {
      return 0;
    } else if (output > 100) {
      return 100;
    } else {
      return output;
    }
}

void RotationalAndTranslationalTracking2(void) {
    int imageHalfHeight = IMAGE_HEIGHT / 2;
    int objectYLocation = imageHalfHeight;
    int imageHalfWidth = IMAGE_WIDTH / 2;
    int objectXLocation = imageHalfWidth;
    int objectCount = 0;
    int rotationalTolerance = 20;
    int translationalTolerance = 8;
    int leftMotorPower = 0;
    int rightMotorPower = 0;
    int yPowerComponent = 0;

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
            if ( objectYLocation < 97 ) {
                yPowerComponent = 100 - NormalizeSensorReading(objectYLocation, 0, 97);
                leftMotorPower += yPowerComponent;
                rightMotorPower += yPowerComponent;
            }

            printf("\nY Power component is %d", yPowerComponent);
            leftMotorPower /= 2;
            rightMotorPower /= 2;


            // Check if the objectXLocation is outside of the tolerance
            if ( objectXLocation < 80 - 2 || objectXLocation > 80 + 2 ) {
                if (objectXLocation < imageHalfWidth) {
                     rightMotorPower += 100 - NormalizeSensorReading(objectXLocation, 0, imageHalfWidth);
                } else {
                     leftMotorPower += NormalizeSensorReading(objectXLocation, imageHalfWidth, IMAGE_WIDTH);
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
