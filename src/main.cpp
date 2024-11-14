#include <Arduino.h>
#include <ESP32Servo.h>
#include <NewPing.h>
#include "Car.h"
#include "config.h"

// Initialize components
NewPing sonar(TRIG_PIN, ECHO_PIN);
Servo servo;
Car car(ENA_PIN, ENB_PIN, RF, LF, LB, RB);
int distance = 0;

int readPing()
{
  delay(150);
  int cm = sonar.ping_cm();
  Serial.print("Current Distance: ");
  Serial.println(cm);
  if (cm == 0)
  {
    Serial.println("Ultrasonic sensor not found!");
  }
  return cm;
}

// Servo control functions
void servoFront()
{
  servo.write(90);
}

void servoLeft()
{
  servo.write(180);
}

void servoRight()
{
  servo.write(0);
}

int leftDistance()
{
  servoLeft();
  delay(SERVO_DELAY);
  int distance = readPing();
  delay(100);
  servoFront();
  return distance;
}

int rightDistance()
{
  servoRight();
  delay(SERVO_DELAY);
  int distance = readPing();
  delay(100);
  servoFront();
  return distance;
}

int calculateTurn()
{
  delay(300);
  int left = leftDistance();
  delay(300);
  int right = rightDistance();
  delay(300);

  if (left >= right)
  {
    return -1; // Left is clear
  }
  else if (right >= left)
  {
    return 1; // Right is clear
  }

  return 0; // No clear turn direction
}

void handleTurn()
{
  int dir = calculateTurn();

  if (dir == -1)
  {
    car.setSpeed(255);
    car.turnLeft();
    delay(800);
    car.moveForward();
    delay(100);
    car.setSpeed(INITIAL_SPEED);
    car.stop();
  }
  else if (dir == 1)
  {
    car.setSpeed(255);
    car.turnRight();
    delay(800);
    car.moveForward();
    delay(100);
    car.setSpeed(INITIAL_SPEED);
    car.stop();
  }
  else
  {
    car.moveBackward();
    delay(800);
    car.stop();
    handleTurn();
  }
}

// ----------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);
  car.setSpeed(INITIAL_SPEED);
  servo.attach(SERVO_PIN);
  servoFront();
  delay(SERVO_DELAY);

  distance = readPing(); // Measure the distance.
  delay(100);
  distance = readPing(); // Measure again.
  delay(100);
  distance = readPing(); // Measure again.
  delay(100);
  distance = readPing(); // Measure again.
  delay(100);
}

void loop()
{

  // handle if there any object
  if (distance <= 30)
  {
    car.stop();
    delay(300);
    car.moveBackward();
    delay(300);
    car.stop();
    handleTurn();
  }
  else
  {
    car.moveForward();
  }

  distance = readPing();
}
