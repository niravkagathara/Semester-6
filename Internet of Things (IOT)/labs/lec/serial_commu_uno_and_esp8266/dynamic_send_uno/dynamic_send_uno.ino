//uno send dynamic input 
void setup() {
    Serial.begin(9600);  // Start Serial communication
    Serial.println("Arduino Sender Ready! Type a message:");
}

void loop() {
    if (Serial.available()) {  // Check if user input is available
        String userInput = Serial.readStringUntil('\n'); // Read user input
        Serial.println(userInput);  // Send input to ESP8266
    }
}
