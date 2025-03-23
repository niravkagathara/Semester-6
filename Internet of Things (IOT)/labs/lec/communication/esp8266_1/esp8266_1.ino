#include <SoftwareSerial.h>

SoftwareSerial espSerial(2, 3); // RX, TX for ESP8266

void setup() {
  Serial.begin(9600);       // Arduino serial monitor
  espSerial.begin(115200);  // ESP8266 baud rate

  Serial.println("ESP8266 communication started...");

  // Send AT commands to ESP8266
  espSerial.println("AT");
  delay(1000);
}

void loop() {
  if (espSerial.available()) {
    String data = espSerial.readString();
    Serial.print(data);  // Print data from ESP8266 to serial monitor
  }

  if (Serial.available()) {
    String data = Serial.readString();
    espSerial.print(data);  // Send data from serial monitor to ESP8266
  }
}
