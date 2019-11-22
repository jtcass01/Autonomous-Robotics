#include "pid_control.h"

void follow_wall(int goalDistance) {
  int sonarResponseDistance = A_FRONT_SONAR_COLLISION_THRESHOLD_CM+1;
  int lidarResponseDistance = 0;
  int lidarResponse = 0;
  int lidarGoalResponse = ConvertLeftLidarCMToSonarReading(goalDistance);
  int error = 0;
  int derivativeError = 0;
  int integralError = 0;
  int lastError = 0;

  while(sonarResponseDistance >= A_FRONT_SONAR_COLLISION_THRESHOLD_CM) {
    lidarResponse = analog(A_LEFT_LIDAR);
    // Update errors
    error = lidarGoalResponse - lidarResponse;
    derivativeError = (float) error - (float) lastError) / 0.1;
    integralError += error * 0.1;

    leftMotorPower = (float) 50 + PID_WALL_FOLLOW_KP*(float) error + PID_WALL_FOLLOW_KD*derivativeError + PID_WALL_FOLLOW_KI*integralError;
    rightMotorPower = (float) 50 - (PID_WALL_FOLLOW_KP*(float) error + PID_WALL_FOLLOW_KD*derivativeError + PID_WALL_FOLLOW_KI*integralError);

    // Ensure powers are bound by [-100, 100]
    leftMotorPower = bind(leftMotorPower, -100, 100);
    rightMotorPower = bind(rightMotorPower, -100, 100);

    demoMotor(LEFT_MOTOR, RIGHT_MOTOR, leftMotorPower, rightMotorPower);

    // Update last error
    lastError = error;

    // Get front sonar reading
    sonarResponseDistance = ConvertFrontSonarReadingToCM(analog(A_FRONT_SONAR));

    // 10 data points a second.
    msleep(100L);
  }
}
