// Define pins for the flame sensor
const int flameDigitalPin = D0; // Digital pin connected to DO
const int flameAnalogPin = A0;  // Analog pin connected to AO (optional)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  delay(1000);
  Serial.println("Flame Sensor Test");

  // Set the flameDigitalPin as input
  pinMode(flameDigitalPin, INPUT);
}

void loop() {
  // Read the digital value (HIGH/LOW)
  int flameDetected = digitalRead(flameDigitalPin);

  // Read the analog value (optional)
  int flameIntensity = analogRead(flameAnalogPin);

  // Check if flame is detected
  if (flameDetected == LOW) {
    Serial.println("Flame detected!");
  } else {
    Serial.println("No flame detected.");
  }

  // Print analog value (flame intensity)
  Serial.print("Flame Intensity: ");
  Serial.println(flameIntensity);

  delay(1000); // Delay for readability
}
