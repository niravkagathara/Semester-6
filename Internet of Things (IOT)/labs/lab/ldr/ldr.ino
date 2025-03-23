// Define pin numbers
const int lightSensorPin = A0;  // Pin connected to LDR (analog input)
const int lm393Pin = D2;        // Pin connected to LM393 output (digital input)

int lightLevel = 0;             // Variable to store the light sensor value

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Set LM393 pin as input
  pinMode(lm393Pin, INPUT);
}

void loop() {
  // Read the light level from LDR (analog)
  lightLevel = analogRead(lightSensorPin);
  
  // Print the light level to Serial Monitor
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  
  // Check LM393 output to detect whether light is detected
  int sensorState = digitalRead(lm393Pin);  // Read digital output of LM393
  
  if (sensorState == HIGH) {
    Serial.println("Light detected");
  } else {
    Serial.println("No light detected");
  }
  
  delay(500);  // Wait for 500ms before taking another reading
}
