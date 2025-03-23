#include <SoftwareSerial.h>

SoftwareSerial softSerial(D2, D1); // RX, TX

void setup() {
    Serial.begin(115200); // Monitor input
    softSerial.begin(9600); // Communication with receiver
    Serial.println("ESP8266 Sender Ready! Enter text to send:");
}

void loop() {
    if (Serial.available()) {  // Check if user input is available
        String userInput = Serial.readStringUntil('\n'); // Read input
        softSerial.println(userInput);  // Send input via SoftwareSerial
        Serial.println("Sent: " + userInput);
    }
}
