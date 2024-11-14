// Car.h
#ifndef CAR_H
#define CAR_H

#include <Arduino.h>

class Car
{
public:
  Car(int enable1, int enable2, int rf, int lf, int lb, int rb);
  void setSpeed(int speed);
  void moveForward();
  void moveBackward();
  void turnLeft();
  void turnRight();
  void stop();
  void handleHorn(bool hornState);
  void toggleFrontLED(bool state);
  void toggleBackLED(bool state);
  void update();

private:
  int _enable1, _enable2;
  int _rf, _lf, _lb, _rb;
  int _dutyCycle;
  bool _isHornActive;
  unsigned long _hornStartTime;
  const unsigned long _hornDuration = 500; // milliseconds

  void updateHorn();
};

#endif // CAR_H
