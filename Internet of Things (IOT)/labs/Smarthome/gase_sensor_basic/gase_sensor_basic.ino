// Define the analog pin where the sensor is connected
const int gasSensorPin = A0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  Serial.println("Gas Sensor Test with ESP8266");
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(gasSensorPin);

  // Print the sensor value to the Serial Monitor
  Serial.print("Gas Sensor Value: ");
  Serial.println(sensorValue);

  // Add a delay for stability
  delay(1000); // Wait for 1 second before the next reading
}