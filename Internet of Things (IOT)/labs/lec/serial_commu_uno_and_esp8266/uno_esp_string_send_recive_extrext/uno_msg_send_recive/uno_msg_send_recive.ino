// New code of Send data from UNO

#include <SoftwareSerial.h>
#include <DHT.h>

SoftwareSerial espSerial(2, 3); // RX (Arduino), TX (ESP8266)

// Sensor Pins
#define LDR_SENSOR A0
#define GAS_SENSOR A1
#define FLAME_SENSOR A2
#define MOTION_SENSOR 5

#define OBSTACLE_SENSOR 6
#define MOISTURE_SENSOR A3
#define TRIG_PIN 10
#define ECHO_PIN 11

// DHT Sensor configuration
#define DHTPIN 4          // Pin connected to DATA pin
#define DHTTYPE DHT11      // Change to DHT22 if you're using it

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

bool dhtEnabled = false;
int dthOnOff;

    


void setup() {
    dht.begin();
    Serial.begin(9600);
    espSerial.begin(9600);

    pinMode(FLAME_SENSOR, INPUT);
    pinMode(MOTION_SENSOR, INPUT);
    pinMode(OBSTACLE_SENSOR, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    // Read sensor values
    if (!dhtEnabled) {
        dthOnOff = 0;
        return;
    }
    if(dthOnOff == 1){
      dhtEnabled;
      return;
    }
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    
    int ldrValue = 0;
    int gasValue = 0;
    int flameStatus =0;
    int motionStatus = 0;
    int obstacleStatus =0;
    int moistureValue = 0;
    // int ldrValue = analogRead(LDR_SENSOR);
    // int gasValue = analogRead(GAS_SENSOR);
    // int flameStatus = digitalRead(FLAME_SENSOR);
    // int motionStatus = digitalRead(MOTION_SENSOR);
    // int obstacleStatus = digitalRead(OBSTACLE_SENSOR);
    // int moistureValue = analogRead(MOISTURE_SENSOR);

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);

    // Ultrasonic Sensor
    // long duration;
    int distance;

    // digitalWrite(TRIG_PIN, LOW);
    // delayMicroseconds(2);
    // digitalWrite(TRIG_PIN, HIGH);
    // delayMicroseconds(10);
    // digitalWrite(TRIG_PIN, LOW);

    // duration = pulseIn(ECHO_PIN, HIGH);
    // distance = duration * 0.034 / 2;
        distance =0;


    // Format and send data as a single string
    String data = String(ldrValue) + "," + String(gasValue) + "," + 
                  String(flameStatus) + "," + String(motionStatus) + "," + 
                  String(temperature) + "," + String(humidity) + "," + String(obstacleStatus) + "," + 
                  String(moistureValue) + "," + String(distance)+","+String(dthOnOff);

    //Send dta to MCU
    espSerial.println(data);
    Serial.println("Sent: " + data);

        delay(2000); // Adjust delay as needed

    // Receive data from ESP8266 and display it
    
    // if (espSerial.available()) {
    //     String receivedData = espSerial.readStringUntil('\n'); 
    //     Serial.println("Received: " + receivedData);

    //     // Parse received data
    //     int sensorValues[8]; // Array to store sensor values
    //     int index = 0;
    //     String tempValue = "";

    //     for (int i = 0; i < receivedData.length(); i++) {
    //         if (receivedData[i] == ',') {
    //             sensorValues[index] = tempValue.toInt();
    //             tempValue = "";
    //             index++;
    //         } else {
    //             tempValue += receivedData[i];
    //           }
    //     }
    //     sensorValues[index] = tempValue.toInt(); // Last value

    //   }


}
// #include <SoftwareSerial.h>

// SoftwareSerial espSerial(2, 3); // RX (Arduino), TX (ESP8266)

// // Sensor Pins
// #define LDR_SENSOR A0
// #define GAS_SENSOR A1
// #define FLAME_SENSOR 4
// #define MOTION_SENSOR 5
// #define TEMP_SENSOR A2
// #define OBSTACLE_SENSOR 6
// #define MOISTURE_SENSOR A3
// #define TRIG_PIN 10
// #define ECHO_PIN 11

// void setup() {
//     Serial.begin(9600);
//     espSerial.begin(9600);

//     pinMode(FLAME_SENSOR, INPUT);
//     pinMode(MOTION_SENSOR, INPUT);
//     pinMode(OBSTACLE_SENSOR, INPUT);
//     pinMode(TRIG_PIN, OUTPUT);
//     pinMode(ECHO_PIN, INPUT);
// }

// void loop() {
//     // Read sensor values
//     int ldrValue = analogRead(LDR_SENSOR);
//     int gasValue = analogRead(GAS_SENSOR);
//     int flameStatus = digitalRead(FLAME_SENSOR);
//     int motionStatus = digitalRead(MOTION_SENSOR);
//     int tempValue = analogRead(TEMP_SENSOR);
//     int obstacleStatus = digitalRead(OBSTACLE_SENSOR);
//     int moistureValue = analogRead(MOISTURE_SENSOR);

//     // Ultrasonic Sensor
//     long duration;
//     int distance;

//     digitalWrite(TRIG_PIN, LOW);
//     delayMicroseconds(2);
//     digitalWrite(TRIG_PIN, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TRIG_PIN, LOW);

//     duration = pulseIn(ECHO_PIN, HIGH);
//     distance = duration * 0.034 / 2;

//     // Format and send data as a single string
//     String data = String(ldrValue) + "," + String(gasValue) + "," + 
//                   String(flameStatus) + "," + String(motionStatus) + "," + 
//                   String(tempValue) + "," + String(obstacleStatus) + "," + 
//                   String(moistureValue) + "," + String(distance);

//     espSerial.println(data);
//     Serial.println("Sent: " + data);

//     delay(2000); // Adjust delay as needed
// }