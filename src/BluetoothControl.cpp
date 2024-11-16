#include "BluetoothControl.h"
#include <BluetoothSerial.h>
#include "Config.h"

BluetoothSerial BluetoothControl::ESP_BT;

void BluetoothControl::initialize()
{
  ESP_BT.begin(DEVICE_NAME);
  Serial.print(DEVICE_NAME);
  Serial.println(" : Bluetooth Device is Ready to Pair");
}

bool BluetoothControl::isAvailable()
{
  return ESP_BT.available();
}

int BluetoothControl::read()
{
  return ESP_BT.read();
}
