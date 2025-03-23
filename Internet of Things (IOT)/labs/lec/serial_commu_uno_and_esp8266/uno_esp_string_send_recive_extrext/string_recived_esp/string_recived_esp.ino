#define BLYNK_TEMPLATE_ID "TMPL3562O9RU6"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "pBSYyqwopbuIA_WgYc9wl96s2N1d1tcQ"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// #define BLYNK_TEMPLATE_ID "TMPL3gZJ19PSW"
// #define BLYNK_TEMPLATE_NAME "template2"
// #define BLYNK_AUTH_TOKEN "GKtEIYhHJZaHgepdZmv1Z9qgNBwg52Js"  // Replace with your Blynk Auth Token
bool ultrasonicEnabled = false;
bool moistureEnabled = false;   
bool fireEnabled = false;       
bool dhtEnabled = false;     

float temperature;
float humidity;

SoftwareSerial softSerial(D2, D1); // RX, TX

const char* ssid = "nk";
const char* password = "12345678";

void setup() {
    Serial.begin(115200);
    softSerial.begin(9600);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected!");

    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
}

// BLYNK_WRITE(V12) {  // Toggle Ultrasonic Sensor
//     ultrasonicEnabled = param.asInt();
// }

// BLYNK_WRITE(V13) {  // Toggle Fire Sensor
//     fireEnabled = param.asInt();
// }

// BLYNK_WRITE(V14) {  // Toggle Moisture Sensor
//     moistureEnabled = param.asInt();
// }

BLYNK_WRITE(V15) {  // Toggle DHT Sensor
    dhtEnabled = param.asInt();
}

void loop() {
    Blynk.run();

    if (Serial.available()) {
        String userInput = Serial.readStringUntil('\n'); // Read user input
        softSerial.println(userInput);  // Send input to Arduino
        Serial.println("Sent: " + userInput);
        String data = String(ldrValue) + "," + String(gasValue) + "," + 
                  String(flameStatus) + "," + String(motionStatus) + "," + 
                  String(temperature) + "," + String(humidity) + "," + String(obstacleStatus) + "," + 
                  String(moistureValue) + "," + String(distance);

    //Send dta to MCU
        Serial.println(data);
        softSerial.println("Sent: " + data);
    }
    if (softSerial.available()) {
        String receivedData = softSerial.readStringUntil('\n'); 
        Serial.println("Received: " + receivedData);

        // Parse received data
        int sensorValues[8]; // Array to store sensor values
        int index = 0;
        String tempValue = "";

        for (int i = 0; i < receivedData.length(); i++) {
            if (receivedData[i] == ',') {
                sensorValues[index] = tempValue.toInt();
                tempValue = "";
                index++;
            } else {
                tempValue += receivedData[i];
            }
        }
        sensorValues[index] = tempValue.toInt(); // Last value
        temperature=sensorValues[4];
        humidity=sensorValues[5];
        

        // Send sensor data to Blynk
        // Blynk.virtualWrite(V1, sensorValues[0]); // LDR Sensor
        // Blynk.virtualWrite(V2, sensorValues[1]); // Gas Sensor
        // Blynk.virtualWrite(V3, sensorValues[2]); // Flame Sensor
        // Blynk.virtualWrite(V4, sensorValues[3]); // Motion Sensor
        // Blynk.virtualWrite(V5, sensorValues[4]); // Temperature Sensor
        // Blynk.virtualWrite(V6, sensorValues[5]); // Obstacle Sensor
        // Blynk.virtualWrite(V7, sensorValues[6]); // Moisture Sensor
        // Blynk.virtualWrite(V8, sensorValues[7]); // Ultrasonic Distance
        
    }
    
}

void checkDHT() {

    if (!dhtEnabled) {
        Blynk.virtualWrite(V7, "🚫DHT Sensor Off");
        Blynk.virtualWrite(V8, "🚫DHT Sensor Off");
        return;
    }

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    String tempString = "🌡 " + String(temperature) + " °C";
    String humString = "💧 " + String(humidity) + " %";

     Blynk.virtualWrite(V7, temperature);//temp
    Blynk.virtualWrite(V8, humidity);//hum
}
