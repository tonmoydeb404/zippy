#include "EdgeControl.h"

#define IR_LEFT 23
#define IR_RIGHT 22

void EdgeControl::initialize()
{
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
}

bool EdgeControl::isEdgeDetectedLeft()
{
  return digitalRead(IR_LEFT) == HIGH; // Assume LOW means an edge is detected
}

bool EdgeControl::isEdgeDetectedRight()
{
  return digitalRead(IR_RIGHT) == HIGH; // Assume LOW means an edge is detected
}
