#define SENSOR_PIN A0  // Moisture sensor connected to A0

void setup() {
    Serial.begin(9600);
    pinMode(SENSOR_PIN, INPUT);
}

void loop() {
    int moistureValue = analogRead(SENSOR_PIN);  

    // Convert the raw value to percentage (assuming dry=1024, wet=0)
    int moisturePercent = map(moistureValue, 1024, 0, 0, 100);
    
    Serial.print("Moisture Level: ");
    Serial.print(moisturePercent);
    Serial.println("%");

    delay(1000); 
}
