#define BLYNK_TEMPLATE_ID "TMPL3J9iJJeOP"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "3aE-DfW1o6abaoXnvTOc82dxOpOZJ3hv"  // Replace with your Blynk Auth Token
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "3aE-DfW1o6abaoXnvTOc82dxOpOZJ3hv";  // Replace with your Blynk Auth Token
char ssid[] = "nk";         // Replace with your WiFi SSID
char pass[] = "12345678";     // Replace with your WiFi Password

#define RELAY_PIN 14  // GPIO14 (D5 on NodeMCU)

void setup() {
    Serial.begin(115200);
    Blynk.begin(auth, ssid, pass);
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, HIGH);  // Ensure relay is off initially
}

BLYNK_WRITE(V1) {  // Virtual pin V1 is linked to Blynk button
    int state = param.asInt();  // Read button state (1 = ON, 0 = OFF)
    digitalWrite(RELAY_PIN, state ? LOW : HIGH);  // LOW to activate relay, HIGH to deactivate
}

void loop() {
    Blynk.run();
}
