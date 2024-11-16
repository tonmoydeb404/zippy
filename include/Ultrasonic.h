#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>
#include <NewPing.h>

namespace Ultrasonic
{
  extern NewPing sonar;

  void initialize();
  int ping();
}

#endif
