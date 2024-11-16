#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>

namespace MotorControl
{
  const int freq = 30000;
  const int resolution = 8;
  const int pwmChannel = 0;

  void initialize();
  void idle();
  void disconnect();
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void setSpeed(int speed);
}

#endif
