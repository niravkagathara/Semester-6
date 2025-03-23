#define LDR_PIN A0   // LDR sensor connected to Analog Pin A0
#define LED_PIN D8   // LED connected to GPIO5 (D1) on NodeMCU ESP8266

void setup() {
  Serial.begin(115200);
  Serial.println("LDR Sensor Initialized...");

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off
}

void loop() {
  int ldrValue = analogRead(LDR_PIN); // Read LDR sensor value
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Adjust threshold based on your environment (e.g., 500 for medium brightness)
  if (ldrValue < 500) {  
    digitalWrite(LED_PIN, HIGH);  // Turn on LED at night
    Serial.println("Night detected: LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED during the day
    Serial.println("Day detected: LED OFF");
  }

  delay(1000); // Wait 1 second before next reading
}