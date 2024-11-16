#include <Arduino.h>
#include "BluetoothControl.h"
#include "MotorControl.h"
#include "Ultrasonic.h"
#include "EdgeControl.h"

// Global Variables
int incoming;
int distance = 0;

// ----------------------------------------------------------------------

void handleBluetooth()
{
  // Check if we receive anything from Bluetooth
  if (BluetoothControl::isAvailable())
  {
    incoming = BluetoothControl::read();

    if (incoming != BluetoothControl::IDLE)
    {
      distance = Ultrasonic::ping();
      Serial.print("Incoming: ");
      Serial.println(incoming);
    }

    // Handle commands
    switch (incoming)
    {
    case BluetoothControl::IDLE:
      MotorControl::idle();
      break;
    case BluetoothControl::DISCONNECT:
      MotorControl::disconnect();
      break;
    case BluetoothControl::FORWARD:
      if (distance <= 30)
      {
        MotorControl::idle();
      }
      else if (EdgeControl::isEdgeDetectedLeft())
      {
        MotorControl::idle();
        MotorControl::moveBackward();
        delay(300);
        MotorControl::turnRight();
        delay(500);
      }
      else if (EdgeControl::isEdgeDetectedRight())
      {
        MotorControl::idle();
        MotorControl::moveBackward();
        delay(300);
        MotorControl::turnLeft();
        delay(500);
      }
      else if (EdgeControl::isEdgeDetectedLeft() && EdgeControl::isEdgeDetectedRight())
      {
        MotorControl::idle();
        MotorControl::moveBackward();
        delay(500);
      }
      else
      {
        MotorControl::moveForward();
      }

      break;
    case BluetoothControl::BACKWARD:
      MotorControl::moveBackward();
      break;
    case BluetoothControl::LEFT:
      MotorControl::turnLeft();
      break;
    case BluetoothControl::RIGHT:
      MotorControl::turnRight();
      break;
    case BluetoothControl::SPEED0:
    case BluetoothControl::SPEED1:
    case BluetoothControl::SPEED2:
    case BluetoothControl::SPEED3:
    case BluetoothControl::SPEED4:
    case BluetoothControl::SPEED5:
    case BluetoothControl::SPEED6:
    case BluetoothControl::SPEED7:
    case BluetoothControl::SPEED8:
    case BluetoothControl::SPEED9:
    case BluetoothControl::SPEED10:
      MotorControl::setSpeed(incoming);
      break;
    default:
      break;
    }
  }
}

// ----------------------------------------------------------------------

void setup()
{
  Serial.begin(115200); // Start Serial monitor
  Serial.println();

  MotorControl::initialize();
  Ultrasonic::initialize();
  EdgeControl::initialize();
  BluetoothControl::initialize();
}

void loop()
{
  handleBluetooth();

  delay(20);
}
