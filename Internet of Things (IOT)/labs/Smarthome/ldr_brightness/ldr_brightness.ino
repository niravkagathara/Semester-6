// Pin for the LDR
const int LDR_PIN = A0; // Analog pin A0

void setup() {
  Serial.begin(9600); // Initialize serial communication
  delay(1000);          // Wait for the serial monitor to start
  Serial.println("LDR Sensor Test");
}

void loop() {
  // Read analog value from LDR
  int ldrValue = analogRead(LDR_PIN);

  // Print the value to the Serial Monitor
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Add a delay for readability
  delay(1000);
}
