#include "Car.h"

const int freq = 30000;
const int resolution = 8;
const int pwmChannelL = 0;
const int pwmChannelR = 1;

Car::Car(int enable1, int enable2, int rf, int lf, int lb, int rb)
    : _enable1(enable1), _enable2(enable2), _rf(rf), _lf(lf), _lb(lb), _rb(rb), _dutyCycle(0), _isHornActive(false)
{
  pinMode(_rf, OUTPUT);
  pinMode(_lf, OUTPUT);
  pinMode(_lb, OUTPUT);
  pinMode(_rb, OUTPUT);
  pinMode(_enable1, OUTPUT);
  pinMode(_enable2, OUTPUT);

  ledcSetup(pwmChannelR, freq, resolution);
  ledcAttachPin(_enable1, pwmChannelR);
  ledcAttachPin(_enable2, pwmChannelR);
}

void Car::setSpeed(int speed)
{
  _dutyCycle = speed;
  // ledcWrite(pwmChannelL, _dutyCycle);
  ledcWrite(pwmChannelR, _dutyCycle);
}

void Car::moveForward()
{
  digitalWrite(_rf, HIGH);
  digitalWrite(_lb, LOW);
  digitalWrite(_lf, HIGH);
  digitalWrite(_rb, LOW);
}

void Car::moveBackward()
{
  digitalWrite(_rf, LOW);
  digitalWrite(_lb, HIGH);
  digitalWrite(_lf, LOW);
  digitalWrite(_rb, HIGH);
}

void Car::turnLeft()
{
  digitalWrite(_rf, HIGH);
  digitalWrite(_lb, HIGH);
  digitalWrite(_lf, LOW);
  digitalWrite(_rb, LOW);
}

void Car::turnRight()
{
  digitalWrite(_rf, LOW);
  digitalWrite(_lb, LOW);
  digitalWrite(_lf, HIGH);
  digitalWrite(_rb, HIGH);
}

void Car::stop()
{
  digitalWrite(_rf, LOW);
  digitalWrite(_lb, LOW);
  digitalWrite(_lf, LOW);
  digitalWrite(_rb, LOW);
}

void Car::handleHorn(bool hornState)
{
  _isHornActive = hornState;
  updateHorn();
}

void Car::updateHorn()
{
  if (_isHornActive)
  {
    if (millis() - _hornStartTime >= _hornDuration)
    {
      digitalWrite(_enable1, LOW);
      _isHornActive = false;
    }
    else
    {
      digitalWrite(_enable1, HIGH);
      _hornStartTime = millis();
    }
  }
  else
  {
    digitalWrite(_enable1, LOW);
  }
}

void Car::toggleFrontLED(bool state)
{
  digitalWrite(_enable1, state ? HIGH : LOW);
}

void Car::toggleBackLED(bool state)
{
  digitalWrite(_enable2, state ? HIGH : LOW);
}

void Car::update()
{
  updateHorn();
}
