#include "SoftwareSerial.h"

SoftwareSerial BLE(8, 9); // RX, TX

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BLE.begin(9600);
}

void loop() {
  while (BLE.available() > 0)
  {
    char recBLE = BLE.read();
    Serial.println(recBLE);
  }

  while (Serial.available() > 0)
  {
    char sendBLE = Serial.read();
    BLE.write(sendBLE);
  }
}