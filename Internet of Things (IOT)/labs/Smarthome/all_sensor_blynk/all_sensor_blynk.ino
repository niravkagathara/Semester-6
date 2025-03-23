//******************

#define BLYNK_TEMPLATE_ID "TMPL3562O9RU6"
#define BLYNK_TEMPLATE_NAME "Smart Home"
#define BLYNK_AUTH_TOKEN "pBSYyqwopbuIA_WgYc9wl96s2N1d1tcQ"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// #include <BlynkTimer.h>

// WiFi credentials
char ssid[] = "vivek";
char pass[] = "password";

// ldr
#define LDR_PIN D1   // LDR sensor connected to Analog Pin A0
#define LED_PIN D8   // LED connected to GPIO5 (D1) on NodeMCU ESP8266

//motion
#define PIR_PIN D0  // PIR sensor connected to GPIO5 (D1) on NodeMCU ESP8266
#define LED_PIN_M D1  // LED connected to GPIO0 (D3) on NodeMCU ESP8266

int motionCount = 0;
bool motionDetectedPreviously = false;
unsigned long ledOnTime = 0; // Store the time when LED was turned on
bool ledState = false; // Track LED state

//gas
#define GAS_PIN D2   // GPIO14
#define FAN_G D7   // GPIO12

// Flame Sensor
const int flameDigitalPin = D4; // Digital pin connected to DO
// const int flameAnalogPin = A0;  // Analog pin connected to AO
// const int fanPin = D3;          // Fan connected to D3
const int buzzerPin = D4;       // Buzzer connected to D4

// Ultrasonic Sensor
#define TRIG_PIN D5   // GPIO14
#define ECHO_PIN D6   // GPIO12
#define LED_PIN D7    // GPIO13
#define BUZZER_PIN D8 // GPIO15

bool gasEnabled=false;
bool ultrasonicEnabled = false;
bool moistureEnabled = false;   
bool motionEnabled =false;
bool dhtEnabled = false;        
bool fireEnabled = false;    
//Normal Blynk LEDs & Fan
#define LED1 D5
#define FAN D8


// Moisture Sensor
#define SENSOR_PIN A0  // Moisture sensor connected to A0

// DHT Sensor configuration
#define DHTPIN D3          // Pin connected to DATA pin
#define DHTTYPE DHT11      // Change to DHT22 if you're using it

DHT dht(DHTPIN, DHTTYPE);  // Initialize DHT sensor

BlynkTimer timer;

void checkldr(){
  // int ldrValue = analogRead(LDR_PIN); // Read LDR sensor value
    int ldrValue = digitalRead(LDR_PIN); // Read LDR sensor value

  
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Adjust threshold based on your environment (e.g., 500 for medium brightness)
  if (ldrValue == LOW) {  
    digitalWrite(LED_PIN, HIGH);  // Turn on LED at night
    Serial.println("Night detected: LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);   // Turn off LED during the day
    Serial.println("Day detected: LED OFF");
  }
  delay(1000);
}
void checkMoisture() {
    int moistureValue = analogRead(SENSOR_PIN);
    // int moistureValue = digitalRead(SENSOR_PIN);

    if (!moistureEnabled) {
        Blynk.virtualWrite(V5, 0);
        Blynk.virtualWrite(V6, "🚫Moisture Sensor Off");
        return;
    }

    int moisturePercent = map(moistureValue, 1024, 0, 0, 100);
    
    Serial.println("******");
    Serial.print("Moisture Level: ");
    Serial.print(moisturePercent);
    Serial.println("%");
    
    Blynk.virtualWrite(V5, moisturePercent);

    if(moisturePercent>=100){
      Blynk.virtualWrite(V6, "⚠️High Moisture🌱");
    }
    else if(moisturePercent<=30){
      Blynk.virtualWrite(V6, "🫗Low Moisture🌱");
    }
    else{
      Blynk.virtualWrite(V6, "Normal Moisture🌱");
    }
}

void checkDistance() {
    if (!ultrasonicEnabled) {
        Blynk.virtualWrite(V1, 0);  // Send 0 when the sensor is off
        Blynk.virtualWrite(V4, "🚫Parking Sensor Off");
        digitalWrite(LED_PIN, LOW);
        digitalWrite(BUZZER_PIN, LOW);
        return;
    }

    long duration;
    int distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 50000);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    Blynk.virtualWrite(V1, distance);
    digitalWrite(LED_PIN, (distance <= 30) ? HIGH : LOW);

    if (distance <= 3){
      Blynk.virtualWrite(V4, "🛑Stop There!!🛑");
    }else{
      Blynk.virtualWrite(V4, "Be Careful");
    }

    if (distance <= 10 && distance > 3) {
        int buzzerDelay = map(distance, 3, 10, 2, 100);
        digitalWrite(BUZZER_PIN, HIGH);
        delay(buzzerDelay);
        digitalWrite(BUZZER_PIN, LOW);
        delay(buzzerDelay);
    } else if (distance <= 3) {
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        digitalWrite(BUZZER_PIN, LOW);
    }
}

void checkFire() {
    // int flameIntensity = analogRead(flameAnalogPin);
    int flameIntensity = digitalRead(flameDigitalPin);

   if (!fireEnabled) {
        Blynk.virtualWrite(V2, 0);
        Blynk.virtualWrite(V3, "🚫Fire Sensor Off");
        digitalWrite(buzzerPin, LOW);
        // digitalWrite(fanPin, LOW);
        return;
    }

    Blynk.virtualWrite(V2, flameIntensity);

    // if (flameIntensity < 200) {
       if (flameIntensity == HIGH) {
        Serial.println("Fire Alert!!");
        Blynk.virtualWrite(V3, "🔥Fire Alert!🔥");
        digitalWrite(buzzerPin, HIGH);
        delay(500);
        // digitalWrite(fanPin, HIGH);
    } else {
        digitalWrite(buzzerPin, LOW);
        // digitalWrite(fanPin, LOW);
        Blynk.virtualWrite(V3, "No Fire Detected");
    }

    Serial.print("Flame Intensity: ");
    Serial.println(flameIntensity);
}
void checkGas(){
       int GasDetected = digitalRead(GAS_PIN);

   if (!gasEnabled) {
        Blynk.virtualWrite(V16, 0);
        Blynk.virtualWrite(V19, "🚫Gas Sensor Off");
        digitalWrite(LED_PIN_M, LOW);

        return;
    }
    Blynk.virtualWrite(V16, GasDetected); // Send the value to Blynk app
    Serial.print("MQ-5 Gas Value: ");
    Serial.println(GasDetected);
    if (GasDetected < 150) {
    digitalWrite(FAN_G, HIGH); 
    Blynk.virtualWrite(V19, "Clean Air");
    Serial.println("Clean Air");
  } else {
    digitalWrite(FAN_G, LOW);
    Blynk.virtualWrite(V19, "Gas Detected");
    Serial.println("Gas Detected");
  }
}
void checkMotion(){
     int motionDetected = digitalRead(PIR_PIN);
    // Serial.print(motionDetected);
   if (!motionEnabled) {
        // Blynk.virtualWrite(V19, 0);
        Blynk.virtualWrite(V18, "🚫Motion Sensor Off");
        digitalWrite(LED_PIN_M, LOW);

        return;
    }
    if (motionDetected == HIGH && !motionDetectedPreviously) {
    motionCount++;
    Serial.print("Motion Count: ");
    Serial.println(motionCount);
    // Blynk.virtualWrite(V19, motionCount);

    if (motionCount == 1) {
      digitalWrite(LED_PIN_M, HIGH); // Turn on LED at first detection
      Serial.println("LED ON (Motion Detected)");
      Blynk.virtualWrite(V18, "LED ON (Motion Detected)");

      ledOnTime = millis(); // Record the time LED was turned on
      ledState = true;
    } 
    // if(motionCount>1){
    //     ledOnTime = millis(); // Record the time LED was turned on
    //   ledState = true;
    // }

    motionDetectedPreviously = true; // Mark motion as detected
  } else if (motionDetected == LOW) {
    motionDetectedPreviously = false; // Reset motion detection state
  }

  // Turn off LED after 10 seconds if it was turned on
  if (ledState && millis() - ledOnTime >= 10000) {
    digitalWrite(LED_PIN_M, LOW);
    Serial.println("LED OFF (10 seconds elapsed)");
    Blynk.virtualWrite(V18, "LED OFF (10 seconds elapsed)");

    motionCount = 0; // Reset count
    // Blynk.virtualWrite(V19, motionCount);

    ledState = false;
  }
}
void checkDHT() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

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

    Blynk.virtualWrite(V7, tempString);
    Blynk.virtualWrite(V8, humString);
}

void setup() {
    Serial.begin(115200);
    Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
    dht.begin();

    pinMode(flameDigitalPin, INPUT);
    // pinMode(fanPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    // digitalWrite(fanPin, LOW);
    digitalWrite(buzzerPin, LOW);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(SENSOR_PIN, INPUT);
    pinMode(PIR_PIN, INPUT);
    pinMode(LED_PIN_M, OUTPUT);
    pinMode(FAN_G, OUTPUT);
    pinMode(GAS_PIN, INPUT);

     pinMode(LED1,OUTPUT);
    digitalWrite(LED1,LOW);
    pinMode(FAN,OUTPUT);
    digitalWrite(FAN,LOW);
   pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW); // Start with LED off
    timer.setInterval(1000L, checkFire);
    timer.setInterval(1000L, checkDistance);
    timer.setInterval(1000L, checkMoisture);
    timer.setInterval(1000L, checkMotion);
    timer.setInterval(1000L, checkGas);
    timer.setInterval(2000L, checkDHT);
}

// Get values from Blynk
BLYNK_WRITE(V9) {
  int led1State = param.asInt(); // Get value from Blynk app (0 or 1)
  digitalWrite(LED1, !led1State); // Set LED1 state
}



BLYNK_WRITE(V11) {
  int fanState = param.asInt(); // Get value from Blynk app (0 or 1)
  digitalWrite(FAN, fanState); // Set FAN state
}

BLYNK_WRITE(V12) {  // Toggle Ultrasonic Sensor
    ultrasonicEnabled = param.asInt();
}

BLYNK_WRITE(V13) {  // Toggle Fire Sensor
    fireEnabled = param.asInt();
}

BLYNK_WRITE(V14) {  // Toggle Moisture Sensor
    moistureEnabled = param.asInt();
}

BLYNK_WRITE(V15) {  // Toggle DHT Sensor
    dhtEnabled = param.asInt();
}

BLYNK_WRITE(V17) {  // Toggle motion Sensor
    motionEnabled = param.asInt();
}

BLYNK_WRITE(V20) {  // Toggle Gas Sensor
    gasEnabled = param.asInt();
}
void loop() {
    Blynk.run();
    timer.run();
    checkldr();

}