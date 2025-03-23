#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Create a SoftwareSerial object to communicate with the GPS
SoftwareSerial ss(4, 5); // RX, TX (choose appropriate pins)

// Create an instance of the TinyGPS++ library
TinyGPSPlus gps;

void setup() {
  // Start the serial communication with ESP8266 and GPS
  Serial.begin(115200);  // ESP8266 Serial Monitor
  ss.begin(9600);        // GPS Serial communication

  Serial.println("GPS Basic Code with ESP8266");
}

void loop() {
  // Continuously read data from the GPS module
  while (ss.available() > 0) {
    gps.encode(ss.read());
    
    // Check if a new GPS data is available
    if (gps.location.isUpdated()) {
      // Get latitude and longitude
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
      
      // Print the coordinates
      Serial.print("Latitude= "); 
      Serial.print(latitude, 6);
      Serial.print(" Longitude= "); 
      Serial.println(longitude, 6);
    }
  }
}
