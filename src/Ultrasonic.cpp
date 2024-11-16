#include "Ultrasonic.h"
#include "Config.h"

// Create a NewPing object
NewPing Ultrasonic::sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void Ultrasonic::initialize()
{
  // Initialize the ultrasonic sensor
  Serial.println("Ultrasonic sensor initialized.");
}

int Ultrasonic::ping()
{

  int distance = sonar.ping_cm();

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance == 0)
  {
    // If no echo received, return the max distance
    return MAX_DISTANCE;
  }
  return distance;
}
