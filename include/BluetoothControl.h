#ifndef BLUETOOTH_CONTROL_H
#define BLUETOOTH_CONTROL_H

#include <BluetoothSerial.h>

namespace BluetoothControl
{

  // Command Definitions
  const int IDLE = 83;
  const int DISCONNECT = 68;
  const int FORWARD = 70;
  const int BACKWARD = 66;
  const int LEFT = 76;
  const int RIGHT = 82;
  const int SPEED0 = 48;
  const int SPEED1 = 49;
  const int SPEED2 = 50;
  const int SPEED3 = 51;
  const int SPEED4 = 52;
  const int SPEED5 = 53;
  const int SPEED6 = 54;
  const int SPEED7 = 55;
  const int SPEED8 = 56;
  const int SPEED9 = 57;
  const int SPEED10 = 113;

  extern BluetoothSerial ESP_BT;

  void initialize();
  bool isAvailable();
  int read();
} // namespace BluetoothControl

#endif
