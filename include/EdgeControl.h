#ifndef EDGE_CONTROL_H
#define EDGE_CONTROL_H

#include <Arduino.h>

class EdgeControl
{
public:
  static void initialize();
  static bool isEdgeDetectedLeft();
  static bool isEdgeDetectedRight();
};

#endif
