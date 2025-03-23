#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define LED D1 // GPIO 5 (D1) for LED
bool ledState = false;
#define TRIG_PIN D5 // GPIO14
#define ECHO_PIN D6 // GPIO12

// WiFi settings
const char *ssid = "nk";
const char *password = "12345678";
// MQTT Broker settings
const char *mqtt_broker = "e8ba45b893c347c996853874ede3107c.s1.eu.hivemq.cloud";// EMQX broker endpoint
const char *mqtt_topic = "Nirav";// MQTT topic
const char *mqtt_username = "niravkagathara4"; 
const char *mqtt_password = "Nirav@9313"; 
const int mqtt_port = 1883; 
const char *data;
  char buffer[20];  // Make sure the buffer is large enough for your number
WiFiClient espClient;  // Normal WiFiClient

// WiFiClientSecure espClient;
PubSubClient mqtt_client(espClient);

void connectToWiFi();

void connectToMQTTBroker();

void mqttCallback(char *topic, byte *payload, unsigned int length);

void setup() {
 Serial.begin(115200);
 connectToWiFi();
  Serial.println("Ultrasonic Sensor Test");

  // Set TRIG as OUTPUT and ECHO as INPUT
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED, OUTPUT);

 mqtt_client.setServer(mqtt_broker, mqtt_port);
 mqtt_client.setCallback(mqttCallback);
 connectToMQTTBroker();
}

void connectToWiFi() {
 WiFi.begin(ssid, password);
 Serial.print("Connecting to WiFi");
 while (WiFi.status() != WL_CONNECTED) {
delay(500);
 Serial.print(".");
   }
 Serial.println("\nConnected to the WiFi network");
}

void connectToMQTTBroker() {
 while (!mqtt_client.connected()) {
 String client_id = "nirav";
 Serial.printf("Connecting to MQTT Broker as %s.....\n", client_id.c_str());
 if (mqtt_client.connect(client_id.c_str()),mqtt_username,mqtt_password) {
 Serial.println("Connected to MQTT broker");
 mqtt_client.subscribe(mqtt_topic);
 mqtt_client.publish(mqtt_topic, "welcome");
   } else {
 Serial.print("Failed to connect to MQTT broker, rc=");
 Serial.print(mqtt_client.state());
 Serial.println(" try again in 5 seconds");
 delay(5000);
   }
   }
}

void mqttCallback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message received on topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 String message;
 for (int i = 0; i < length; i++) {
 message += (char) payload[i];
   }
 if (message == "on" && !ledState) {
 digitalWrite(LED, HIGH);
 ledState = true;
 Serial.println("LED is turned on");
   }
 if (message == "off" && ledState) {
 digitalWrite(LED, LOW); // Turn off the LED
 ledState = false;
 Serial.println("LED is turned off");
   }
 Serial.println();
 Serial.println("-----------------------");
}

void loop() {
 if (!mqtt_client.connected()) {
 connectToMQTTBroker();
   }
 mqtt_client.loop();
 long duration, distance;

  // Generate a 10µs pulse to TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure the pulse duration from ECHO pin
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm
  distance = duration * 0.034 / 2;
    sprintf(buffer, "%ld", distance);
  data=buffer;
String newData = String(data) + " cm";  // Concatenates "123" and "cm"
  // Print the distance
  const char* data = newData.c_str();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
   mqtt_client.publish(mqtt_topic, data);
  delay(2000);

}
