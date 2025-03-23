const int gasSensorPin = A0;  // Analog pin connected to the gas sensor

void setup() {
  Serial.begin(9600);  // Start the Serial Monitor
  Serial.println("Gas Sensor Ready!");
}

void loop() {
  int sensorValue = analogRead(gasSensorPin);  // Read gas sensor value
  Serial.print("Gas Sensor Value: ");
  Serial.println(sensorValue);  // Print value to Serial Monitor
  delay(1000);  // Wait 1 second
}
