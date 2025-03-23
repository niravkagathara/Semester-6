#define BLYNK_TEMPLATE_ID "TMPL338h54R6f"
#define BLYNK_TEMPLATE_NAME "dev"
#define BLYNK_AUTH_TOKEN "cC4dwlwJf9o_-YUjfdODl2k07iqvUo4E"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Mr.Dev";
char pass[] = "12345678";

BlynkTimer timer; // Create a BlynkTimer object

WidgetLCD lcd(V2); // Attach a virtual LCD widget to Virtual Pin V2

void setup() {
  pinMode(D6, OUTPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent); // Set timer to call myTimerEvent every second
}

void myTimerEvent() {
  int sensorValue = analogRead(A0); // Read the analog value from MQ-5
  Blynk.virtualWrite(V1, sensorValue); // Send the value to Blynk app
  Serial.print("MQ-5 Sensor Value: ");
  Serial.println(sensorValue);

  lcd.clear(); // Clear the previous display
  if (sensorValue < 150) {
    digitalWrite(D6, HIGH); 
    Serial.println("Clean Air");
  } else {
    digitalWrite(D6, LOW);
    Serial.println("Gas Detected");
  }
}

void loop() {
  Blynk.run();
  timer.run(); // Run the BlynkTimer
}