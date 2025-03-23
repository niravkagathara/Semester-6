#include <Wire.h>

void setup() {
  Wire.begin(D2, D1); // SDA = D2, SCL = D1
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
}

void loop() {
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  delay(1000);
}
