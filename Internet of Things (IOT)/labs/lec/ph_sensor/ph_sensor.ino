// Define pin for the pH sensor
const int pHSensorPin = A0;  // A0 is the analog input pin on ESP8266

// Variable to store the pH sensor value
int pHValue = 0;

void setup() {
  // Start serial communication
  Serial.begin(115200);
  delay(1000);
  Serial.println("pH Sensor with ESP8266");
}

void loop() {
  // Read the analog value from the pH sensor
  pHValue = analogRead(pHSensorPin);
  
  // Print the raw value (0 to 1023 range)
  Serial.print("Raw pH Sensor Value: ");
  Serial.println(pHValue);

  // Convert the raw sensor value to pH value (this step depends on your sensor's calibration)
  float voltage = pHValue * (3.3 / 1023.0);  // Convert the raw value to voltage (using 3.3V reference)
  
  // Assuming a linear relation (this will need to be adjusted based on your sensor's calibration)
  // pH = (voltage - 2.5) * 3.0; // For example, a formula for some sensors, where 2.5V is neutral pH and 3.0 is the scale factor.
  
  // For demonstration purposes, let's assume a simplified conversion
  float pH = (voltage - 2.5) * 3.0;
  
  // Print the pH value
  Serial.print("Calculated pH Value: ");
  Serial.println(pH);

  delay(1000);  // Wait for 1 second before reading again
}
