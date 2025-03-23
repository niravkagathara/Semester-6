#include <SoftwareSerial.h>

SoftwareSerial softSerial(D2, D1); // RX, TX

void setup() {
    Serial.begin(115200);
    softSerial.begin(9600);
    Serial.println("ESP8266 Ready! Type a message:");
}

void loop() {
    // Check if user input is available from Serial Monitor
    if (Serial.available()) {
        String userInput = Serial.readStringUntil('\n'); // Read input
        softSerial.println(userInput);  // Send input via SoftwareSerial
        Serial.println("Sent: " + userInput);
    }

    // Check if data is received from the other ESP8266
    if (softSerial.available()) {
        String receivedData = softSerial.readStringUntil('\n');
        Serial.println("Received: " + receivedData);
    }
}
