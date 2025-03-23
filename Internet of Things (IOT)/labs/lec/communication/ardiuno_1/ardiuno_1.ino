void setup() {
  Serial.begin(9600);    // Initialize serial communication with Arduino
  Serial1.begin(115200); // Initialize serial communication with ESP8266 (change baud rate as needed)
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();       // Read data from Arduino Serial Monitor
    Serial1.write(data);             // Send data to ESP8266
  }

  if (Serial1.available()) {
    char data = Serial1.read();      // Read data from ESP8266
    Serial.write(data);              // Send data to Arduino Serial Monitor
  }
}
