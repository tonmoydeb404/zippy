#include "MotorControl.h"
#include "Config.h"

int dutyCycle = 100;

void MotorControl::initialize()
{
  pinMode(RF, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);

  // Configure PWM
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(ENA_PIN, pwmChannel);
  ledcAttachPin(ENB_PIN, pwmChannel);

  // Set default state
  idle();
}

void MotorControl::idle()
{
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(RB, LOW);
}

void MotorControl::disconnect()
{
  Serial.println("Bluetooth Disconnected!");
  idle();
}

void MotorControl::moveForward()
{
  digitalWrite(RF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(LF, HIGH);
  digitalWrite(RB, LOW);
}

void MotorControl::moveBackward()
{
  digitalWrite(RF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(LF, LOW);
  digitalWrite(RB, HIGH);
}

void MotorControl::turnLeft()
{
  digitalWrite(RF, HIGH);
  digitalWrite(LB, HIGH);
  digitalWrite(LF, LOW);
  digitalWrite(RB, LOW);
}

void MotorControl::turnRight()
{
  digitalWrite(RF, LOW);
  digitalWrite(LB, LOW);
  digitalWrite(LF, HIGH);
  digitalWrite(RB, HIGH);
}

void MotorControl::setSpeed(int speed)
{
  int speedLevels[] = {0, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240};
  for (int i = 0; i < 11; i++)
  {
    if (speed == (48 + i) || (i == 10 && speed == 113))
    {
      dutyCycle = speedLevels[i];
      ledcWrite(pwmChannel, dutyCycle);
      break;
    }
  }
}
