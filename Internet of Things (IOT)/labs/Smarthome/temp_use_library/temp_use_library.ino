#include <DHT.h>

// DHT Sensor configuration
#define DHTPIN 2          // Pin connected to DATA pin
#define DHTTYPE DHT11      // Change to DHT22 if you're using it

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

void setup() {
  Serial.begin(9600);      // Start Serial Monitor
  dht.begin();             // Initialize DHT sensor
  Serial.println("DHT Sensor is ready!");
}

void loop() {
  // Read temperature and humidity
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity in %

  // Check if reading was successful
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);  // Wait 2 seconds before retrying
    return;
  }

  // Print the readings to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Wait 2 seconds before the next reading
  delay(2000);
}
