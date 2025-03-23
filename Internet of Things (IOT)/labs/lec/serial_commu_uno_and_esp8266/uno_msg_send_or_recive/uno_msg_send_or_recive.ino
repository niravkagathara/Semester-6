//esp8266 send and recive both msg
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPL3gZJ19PSW"
#define BLYNK_TEMPLATE_NAME "template2"
#define BLYNK_AUTH_TOKEN "GKtEIYhHJZaHgepdZmv1Z9qgNBwg52Js"  // Replace with your Blynk Auth Token


SoftwareSerial softSerial(D2, D1); // RX, TX

const char* ssid = "nk";            // WiFi Network Name
const char* password = "12345678";  // WiFi Password

int ledPin = LED_BUILTIN; // Define the LED pin (e.g., GPIO5 for D1)

void wificonnecta() {
  Serial.println("\nConnecting to WiFi...");
  WiFi.begin(ssid, password);  // Connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address
}

void setup() {
    Serial.begin(115200);
    softSerial.begin(9600);

    wificonnecta();
    pinMode(ledPin, OUTPUT); // Set LED pin as output
    digitalWrite(ledPin, LOW); // Ensure LED is off at the start // Start Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
    Serial.println("ESP8266 Ready! Type a message:");
}

BLYNK_WRITE(V1) {
  int ledState = param.asInt(); // Get value from Blynk app (0 or 1)
  digitalWrite(ledPin, ledState); // Set LED state
}

void loop() {
    Blynk.run(); // Run the Blynk process
    // Check if user input is available
    if (Serial.available()) {
        String userInput = Serial.readStringUntil('\n'); // Read user input
        softSerial.println(userInput);  // Send input to Arduino
        Serial.println("Sent: " + userInput);
    }

    // Check if data is received from Arduino Uno
    if (softSerial.available()) {
        String receivedData = softSerial.readStringUntil('\n');
        Serial.println("Received from Arduino: " + receivedData);
    }
}
