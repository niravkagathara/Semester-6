const int flameAnalogPin = A0; // Analog pin connected to AO

// Adjust these values based on room and flame testing
float analogMin = 200.0;  // Baseline analog value (room environment)
float analogMax = 900.0;  // Analog value for strong flame
float tempMin = 25.0;     // Room temperature in Celsius
float tempMax = 300.0;    // Maximum flame temperature in Celsius

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Flame Sensor with Calibrated Temperature Output");
}

void loop() {
  int flameIntensity = analogRead(flameAnalogPin);

  if (flameIntensity <= analogMin) {
    // Room temperature or no flame
    Serial.println("No flame detected. Room temperature.");
  } else {
    // Map the flame intensity to temperature
    float temperatureCelsius = map(flameIntensity, analogMin, analogMax, tempMin, tempMax);
    float temperatureFahrenheit = (temperatureCelsius * 9.0 / 5.0) + 32.0;

    Serial.print("Flame Intensity (Analog): ");
    Serial.print(flameIntensity);
    Serial.print(" | Temperature: ");
    Serial.print(temperatureCelsius);
    Serial.print(" °C / ");
    Serial.print(temperatureFahrenheit);
    Serial.println(" °F");
  }

  delay(1000);
}
