//esp8266 recuve dynamic msg
#include <SoftwareSerial.h>

SoftwareSerial softSerial(D2, D1); // RX, TX

void setup() {
    Serial.begin(115200);
    softSerial.begin(9600);
    Serial.println("ESP8266 Receiver Ready");
}

void loop() {
    if (softSerial.available()) {  // Check if data is received
        String receivedData = softSerial.readStringUntil('\n'); // Read input
        Serial.println("Received: " + receivedData);  // Display message
    }
}
