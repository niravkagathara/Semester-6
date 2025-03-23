//ultra ,motion,mosture,gas

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// WiFi Credentials
const char* ssid = "nk";
const char* password = "12345678";

// MQTT Broker (HiveMQ Cloud)
const char* mqtt_server = "e8ba45b893c347c996853874ede3107c.s1.eu.hivemq.cloud";
const int mqtt_port = 8883;
const char* mqtt_user = "SmartHome";
const char* mqtt_password = "Smart@1234";
const char* receiveTopic = "nirav";

String receivedTopic = "";
String receivedMessage = "";

WiFiClientSecure espClient;
PubSubClient client(espClient);

//motion
#define PIR_PIN D0    // PIR sensor connected to GPIO5 (D1) on NodeMCU ESP8266
#define LED_PIN_M D1  // LED connected to GPIO0 (D3) on NodeMCU ESP8266
int motionCount = 0;
bool motionDetectedPreviously = false;
unsigned long ledOnTime = 0;  // Store the time when LED was turned on
unsigned long motionStartTime = 0;  // Store the time when motion is detected
bool motionDetected = false;        // Flag to indicate if motion was detected

bool ledState = false;        // Track LED state

const char* motionTopic = "smarthome/motion";
const char* motionvalue = "smarthome/motion/value";
const char* motionControlTopic = "smarthome/motion/control";
const char* motiononoff = "smarthome/motion/onoff";

//gas
#define GAS_PIN D2  // GPIO14
#define FAN_G D3    // GPIO12
const char* gasTopic = "smarthome/gas";
const char* gasvalue = "smarthome/gas/value";
const char* gasControlTopic = "smarthome/gas/control";
const char* gasonoff = "smarthome/gas/onoff";

// Ultrasonic Sensor
#define TRIG_PIN D5    // GPIO14
#define ECHO_PIN D6    // GPIO12
#define LED_PIN D7     // GPIO13
#define BUZZER_PIN D8  // GPIO15
const char* ultraTopic = "smarthome/ultrasonic";
const char* ultravalue = "smarthome/ultrasonic/value";
const char* ultraControlTopic = "smarthome/ultrasonic/control";
const char* ultraonoff = "smarthome/ultrasonic/onoff";

// Moisture Sensor
#define SENSOR_PIN A0  // Moisture sensor connected to A0
const char* moistureTopic = "smarthome/moisture";
const char* moisturevalue = "smarthome/moisture/value";
const char* moistureControlTopic = "smarthome/moisture/control";
const char* moistureonoff = "smarthome/moisture/onoff";

const char* allsensoronoff = "smarthome/onoff/device1";
const char* allsensorValue = "smarthome/value/device1";


bool gasEnabled = false;
bool ultrasonicEnabled = false;
bool moistureEnabled = false;
bool motionEnabled = false;
bool allsensor= false;

void setup_wifi() {
  // Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
  }
  // Serial.println("\n✅ WiFi Connected");
  // Serial.print("IP Address: ");
  // Serial.println(WiFi.localIP());
}
void reconnect() {
  while (!client.connected()) {
    // Serial.print("🔄 Connecting to MQTT...");
    if (client.connect("NodeMCU_Clientab", mqtt_user, mqtt_password)) {
      Serial.println("✅ Connected to MQTT");
      client.subscribe(receiveTopic);
      client.subscribe(gasControlTopic);
      client.subscribe(ultraControlTopic);
      client.subscribe(moistureControlTopic);
      client.subscribe(motionControlTopic);
      client.subscribe(allsensoronoff);

      client.publish(receiveTopic, "welcome esp");
    } else {
      // Serial.print("❌ Failed (Error Code: ");
      Serial.print(client.state());
      // Serial.println("). Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.println(topic);
  receivedTopic = String(topic);
  receivedMessage = "";
  for (int i = 0; i < length; i++) {
    receivedMessage += (char)payload[i];
  }
  Serial.print("Message: ");
  Serial.println(receivedMessage);
  Serial.println("-----------------------");

  // Handling received messages
  buttons();
}
void buttons() {
  if (receivedTopic == gasControlTopic) {
    if (receivedMessage == "ON") {
      gasEnabled = true;
      publishData(gasonoff, 1);
      Serial.println("gas sensor is on");

    } else if (receivedMessage == "OFF") {
      gasEnabled = false;
      publishData(gasonoff, 0);
      publishData(gasvalue, 0);
      Serial.println("gas sensor is off");
    }
  } else if (receivedTopic == ultraControlTopic) {
    if (receivedMessage == "ON") {
      ultrasonicEnabled = true;
      publishData(ultraonoff, 1);
      // Serial.println("ultrasonic Sensor on");

    } else if (receivedMessage == "OFF") {
      ultrasonicEnabled = false;
      publishData(ultraonoff, 0);
      publishData(ultravalue, 0);
      // Serial.println("🚫ultrasonic Sensor Off");
    }
  } else if (receivedTopic == moistureControlTopic) {
    if (receivedMessage == "ON") {
      moistureEnabled = true;
      publishData(moistureonoff, 1);
      // Serial.println("Moisture sensor is on");

    } else if (receivedMessage == "OFF") {
      moistureEnabled = false;
      publishData(moistureonoff, 0);
      publishData(moisturevalue, 0);
      // Serial.println("Moisture sensor is off");
    }
  } else if (receivedTopic == motionControlTopic) {
    if (receivedMessage == "ON") {
      motionEnabled = true;
      publishData(motiononoff, 1);
      // Serial.println("motion Sensor on");

    } else if (receivedMessage == "OFF") {
      motionEnabled = false;
      publishData(motiononoff, 0);
      publishData(motionvalue, 0);
      // Serial.println("🚫motion Sensor Off");
    }
  }
  else if (receivedTopic == allsensoronoff) {
    if (receivedMessage == "ON") {
      allsensor=true;
      motionEnabled = true;
      gasEnabled = true;
      ultrasonicEnabled = true;
      moistureEnabled = true;

      publishData(motiononoff, 1);
      publishData(gasonoff, 1);
      publishData(ultraonoff, 1);
      publishData(moistureonoff, 1);
      // Serial.println("all Sensor on");

    } else if (receivedMessage == "OFF") {
      allsensor=false;
      motionEnabled = false;
      gasEnabled = false;
      ultrasonicEnabled = false;
      moistureEnabled = false;
      publishData(motiononoff, 0);
      publishData(gasonoff, 0);
      publishData(ultraonoff, 0);
      publishData(moistureonoff, 0);
      publishData(motionvalue, 0);
      publishData(gasvalue, 0);
      publishData(ultravalue, 0);
      publishData(moisturevalue, 0);
      // Serial.println("all Sensor Off");
    }
  }
}
void publishData(const char* topic, const String& message) {
  client.publish(topic, message.c_str());
  // delay(500);
}
void publishData(const char* topic, int message) {
  String messageStr = String(message);  // Convert integer to String
  client.publish(topic, messageStr.c_str());
  // delay(500);
}
void checkMoisture() {
  int moistureValue = analogRead(SENSOR_PIN);
  if (!moistureEnabled) {
    publishData(moistureTopic, 201);
    publishData(moistureonoff, 0);
    publishData(moisturevalue, 0);
    return;
  }

  int moisturePercent = map(moistureValue, 1024, 0, 0, 100);

  // Serial.println("******************");
  // Serial.print("Moisture Level: ");
  // Serial.print(moisturePercent);
  // Serial.println("%");

  publishData(moistureonoff, 1);
  publishData(moisturevalue, moisturePercent);
  if (moisturePercent >= 100) {
    publishData(moistureTopic, 202);

  } else if (moisturePercent <= 30) {
    publishData(moistureTopic, 203);
  } else {
    publishData(moistureTopic, 204);
  }
}
void checkMotion() {
  int motionState = digitalRead(PIR_PIN);
  // Serial.print(motionDetected);
  if (!motionEnabled) {
    publishData(motionTopic, 205);
    publishData(motiononoff, 0);
    publishData(motionvalue, 0);
    digitalWrite(LED_PIN_M, LOW);

    return;
  }
  publishData(motiononoff, 1);
      publishData(motionvalue, motionState);

  if (motionState == HIGH && !motionDetected) { // Motion detected and not already active
    motionDetected = true;
    motionStartTime = millis();  // Record the time motion was detected
    digitalWrite(LED_PIN_M, HIGH);
          publishData(motionTopic, 206);
    // Serial.println("Motion Detected! LED ON.");
  }
  if (motionDetected && (millis() - motionStartTime >= 10000)) { // Check if 10 seconds have passed
    motionDetected = false;
    digitalWrite(LED_PIN_M, LOW);
        publishData(motionTopic, 207);

    // Serial.println("10 seconds passed. LED OFF.");
  }
  // if (motionDetected == LOW && !motionDetectedPreviously) {
  //   motionCount++;
  //   // Serial.print("Motion Count: ");
  //   // Serial.println(motionCount);
  //   publishData(motionvalue, motionCount);


  //   if (motionCount == 1) {
  //     digitalWrite(LED_PIN_M, HIGH);  // Turn on LED at first detection
  //     // Serial.println("LED ON (Motion Deected)");
  //     publishData(motionTopic, 206);

  //     ledOnTime = millis();  // Record the time LED was turned on
  //     ledState = true;
  //   }
  //   if(motionCount>1){
  //       ledOnTime = millis(); // Record the time LED was turned on
  //     ledState = true;
  //   }
  //   motionDetectedPreviously = true;  // Mark motion as detected
  // } else if (motionDetected == HIGH) {
  //   motionDetectedPreviously = false;  // Reset motion detection state
  // }

  // // Turn off LED after 10 seconds if it was turned on
  // if (ledState && millis() - ledOnTime >= 10000) {
  //   digitalWrite(LED_PIN_M, LOW);
  //   // Serial.println("LED OFF (10 seconds elapsed)");
  //   // Blynk.virtualWrite(V18, "LED OFF (10 seconds elapsed)");
  //   publishData(motionTopic, 207);

  //   motionCount = 0;  // Reset count
  //   ledState = false;
  // }
}
void checkDistance() {
  if (!ultrasonicEnabled) {
    publishData(ultraTopic, 208);
    publishData(ultraonoff, 0);
    publishData(ultravalue, 0);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }
  publishData(ultraonoff, 1);

  long duration;
  int distance;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 50000);
  distance = duration * 0.034 / 2;

  // Serial.print("Distance: ");
  // Serial.print(distance);
  // Serial.println(" cm");
  publishData(ultravalue, distance);
  digitalWrite(LED_PIN, (distance <= 30) ? HIGH : LOW);

  if (distance <= 3) {
    publishData(ultraTopic, 209);

  } else {
    publishData(ultraTopic, 210);
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
void checkGas() {
  int GasDetected = digitalRead(GAS_PIN);
  if (!gasEnabled) {
    publishData(gasTopic, 211);
    publishData(gasonoff, 0);
    publishData(gasvalue, 0);
    digitalWrite(LED_PIN_M, LOW);
    return;
  }
  publishData(gasonoff, 1);
  publishData(gasvalue, GasDetected);

  // Serial.print("MQ-5 Gas Value: ");
  // Serial.println(GasDetected);
  if (GasDetected < 150) {
    digitalWrite(FAN_G, HIGH);
    publishData(gasTopic, 212);
    // Serial.println("Clean Air");
  } else {
    digitalWrite(FAN_G, LOW);
    publishData(gasTopic, 213);
    // Serial.println("Gas Detected");
  }
}
void checkallsensor() {
  if (!allsensor) {
    publishData(allsensorValue, 0);
    // Serial.println("all sensor is off");
    // delay(1000);
    return;
  }
  publishData(allsensorValue, 1);
  // Serial.println("all sensor is ON");
  //  delay(1000);
}
void allsensors() {
  checkMoisture();
  checkMotion();
  checkDistance();
  checkGas();
  checkallsensor();
  delay(500);
}
void setup() {
  Serial.begin(115200);
  //wifi setup check
  setup_wifi();

  //ssl ignore
  espClient.setInsecure();
  espClient.setTimeout(15000);
  //mqtt setup
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  //pinmodes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN_M, OUTPUT);
  pinMode(FAN_G, OUTPUT);
  pinMode(GAS_PIN, INPUT);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  allsensors();
}

// device 1

// ------------------------------------------------------------------------------------------------------------------------------------------
// 201==🚫Moisture Sensor Off const char* moistureTopic = "smarthome/moisture";

// 202==⚠️High Moisture🌱 const char* moistureTopic = "smarthome/moisture";

// 203=="🫗Low Moisture🌱" const char* moistureTopic = "smarthome/moisture";

// 204=="Normal Moisture🌱" const char* moistureTopic = "smarthome/moisture";

// 205=="🚫Motion Sensor Off" const char* motionTopic = "smarthome/motion";

// 206=="LED ON (Motion Detected)" const char* motionTopic = "smarthome/motion";

// 207=="LED OFF (10 seconds elapsed)" const char* motionTopic = "smarthome/motion";

// 208=="🚫Parking Sensor Off" const char* ultraTopic = "smarthome/ultrasonic";

// 209=="🛑Stop There!!🛑" const char* ultraTopic = "smarthome/ultrasonic";

// 210=="Be Careful" const char* ultraTopic = "smarthome/ultrasonic";

// 211=="🚫Gas Sensor Off" const char* gasTopic = "smarthome/gas";

// 212=="Clean Air" const char* gasTopic = "smarthome/gas";

// 213=="Gas Detected" const char* gasTopic = "smarthome/gas";

// device 2

// ------------------------------------------------------------------------------------------------------------------------------------------

// 214=="🚫Temprature Sensor Off" const char* tempTopic = "smarthome/temp";

// 215=="🚫Temprature Sensor Off" const char* humeTopic = "smarthome/hume";

// 216=="ldr is off" const char* ldrTopic = "smarthome/ldr";

// 217=="Night detected: LED ON" const char* ldrTopic = "smarthome/ldr";

// 218=="Day detected: LED OFF" const char* ldrTopic = "smarthome/ldr";

// 219=="🚫Fire Sensor Off" const char* fireTopic = "smarthome/fire";

// 220=="🔥Fire Alert!🔥" const char* fireTopic = "smarthome/fire";

// 221=="No Fire Detected" const char* fireTopic = "smarthome/fire";

// 222=="Failed to read from DHT sensor!"  const char* humeTopic = "smarthome/hume";

// 223=="Failed to read from DHT sensor!" const char* tempTopic = "smarthome/temp";

// ------------------------------------------------------------------------------------------------------------------------------------------

// for api or app 

// publish topic:ON or OFF as user input 

// device 1
// const gasControlTopic = "smarthome/gas/control";
// const ultraControlTopic = "smarthome/ultrasonic/control";
// const moistureControlTopic = "smarthome/moisture/control";
// const motionControlTopic = "smarthome/motion/control";
// const allsensoronoff1 = "smarthome/onoff/device1";
// device 2
// const fanControlTopic = "smarthome/fan";
// const ledControlTopic = "smarthome/led";
// const ldrControlTopic = "smarthome/ldr/control";
// const fireControlTopic = "smarthome/fire/control";
// const tempControlTopic = "smarthome/temp/control";
// const allsensoronoff2 = "smarthome/onoff/device2";



// for esp8266 
// subscribe topic:check message device is on or off

// device 1
// const gasControlTopic = "smarthome/gas/control";
// const ultraControlTopic = "smarthome/ultrasonic/control";
// const moistureControlTopic = "smarthome/moisture/control";
// const motionControlTopic = "smarthome/motion/control";
// const allsensoronoff1 = "smarthome/onoff/device1";
// device 2
// const fanControlTopic = "smarthome/fan";
// const ledControlTopic = "smarthome/led";
// const ldrControlTopic = "smarthome/ldr/control";
// const fireControlTopic = "smarthome/fire/control";
// const tempControlTopic = "smarthome/temp/control";
// const allsensoronoff2 = "smarthome/onoff/device2";


// ------------------------------------------------------------------------------------------------------------------------------------------

// subscribe topic app :

// device 1
// //ldr
// const ldrTopic = "smarthome/ldr";
// const ldrvalue = "smarthome/ldr/value";
// const ldronoff = "smarthome/ldr/onoff";
// //fire
// const fireTopic = "smarthome/fire";
// const firevalue = "smarthome/fire/value";
// const fireonoff = "smarthome/fire/onoff";
// //fan led
// const fanValue = "smarthome/fan/value";
// const ledValue = "smarthome/led/value";
// //temp
// const tempTopic = "smarthome/temp";
// const humeTopic = "smarthome/hume";
// const temponoff = "smarthome/temp/onoff";
// //all sensor for both device
// const allsensorValue2 = "smarthome/value/device2";


// device 1
// //moisture
// const moistureTopic = "smarthome/moisture";
// const moisturevalue = "smarthome/moisture/value";
// const moistureonoff = "smarthome/moisture/onoff";
// //ultra
// const ultraTopic = "smarthome/ultrasonic";
// const ultravalue = "smarthome/ultrasonic/value";
// const ultraonoff = "smarthome/ultrasonic/onoff";
// //gas
// const gasTopic = "smarthome/gas";
// const gasvalue = "smarthome/gas/value";
// const gasonoff = "smarthome/gas/onoff";
// //motion
// const motionTopic = "smarthome/motion";
// const motionvalue = "smarthome/motion/value";
// const motiononoff = "smarthome/motion/onoff";
// //all sensor for both device
// const allsensorValue1 = "smarthome/value/device1";

// ------------------------------------------------------------------------------------------------------------------------------------------

// publish topic app :

// device 1
// //ldr
// const ldrTopic = "smarthome/ldr";
// const ldrvalue = "smarthome/ldr/value";
// const ldronoff = "smarthome/ldr/onoff";
// //fire
// const fireTopic = "smarthome/fire";
// const firevalue = "smarthome/fire/value";
// const fireonoff = "smarthome/fire/onoff";
// //fan led
// const fanValue = "smarthome/fan/value";
// const ledValue = "smarthome/led/value";
// //temp
// const tempTopic = "smarthome/temp";
// const humeTopic = "smarthome/hume";
// const temponoff = "smarthome/temp/onoff";
// //all sensor for both device
// const allsensorValue2 = "smarthome/value/device2";


// device 1
// //moisture
// const moistureTopic = "smarthome/moisture";
// const moisturevalue = "smarthome/moisture/value";
// const moistureonoff = "smarthome/moisture/onoff";
// //ultra
// const ultraTopic = "smarthome/ultrasonic";
// const ultravalue = "smarthome/ultrasonic/value";
// const ultraonoff = "smarthome/ultrasonic/onoff";
// //gas
// const gasTopic = "smarthome/gas";
// const gasvalue = "smarthome/gas/value";
// const gasonoff = "smarthome/gas/onoff";
// //motion
// const motionTopic = "smarthome/motion";
// const motionvalue = "smarthome/motion/value";
// const motiononoff = "smarthome/motion/onoff";
// //all sensor for both device
// const allsensorValue1 = "smarthome/value/device1";



// ------------------------------------------------------------------------------------------------------------------------------------------



// esp8266 topics                                  app topics

// subscribe: check message ON/OFF			publish: msg ON/OFF
// publish: msg code				subscribe: msg code 




// example:
// LDR:

// esp8266:

// publish:
// const char* ldrTopic = "smarthome/ldr";
// const char* ldrvalue = "smarthome/ldr/value";
// const char* ldronoff = "smarthome/ldr/onoff";

// subscribe:
// const char* ldrControlTopic = "smarthome/ldr/control";


// ldrControlTopic check ON/OFF msg if "ON" then sensor send on cmd
// else sensor off cmd

// ldrTopic publish msg code : 217 
// 271 number code msg value is :"Night detected: LED ON"

// ldrvalue publish ldr sensor value 
// ex:54

// ldronoff publish sensor onoff value 
// ex if sensor off then 0 
// else sensor on then publish 1  


// app or api :
// this side oppsite to esp8266

// subscribe:
// const char* ldrTopic = "smarthome/ldr";
// const char* ldrvalue = "smarthome/ldr/value";
// const char* ldronoff = "smarthome/ldr/onoff";

// publish:
// const char* ldrControlTopic = "smarthome/ldr/control";

// subscribe ldrTopic,ldrvalue,ldronoff all topic and show value in app screen api send request every 2 second
// ldrTopic,ldrvalue,ldronoff this topics print msg code 
// and msg code to compair and message print on disply

// publish ldrControlTopic this topic in 
// message ON/OFF

// check ldronoff topic value 0 or 1 then app in set on/off
// example:
// if ldronoff is 0 then in app sensor button is off and user click on button switch now send request ON sensor 
// send msg on topic ldrControlTopic publish message ON



// ------------------------------------------------------------------------------------------------------------------------------------------

// api example:
// api url:http://localhost:3000/get-messages 
// get method
// output:
// {
//     "msg": "mqtt server on",
//     "recived": "welcome esp",
//     "ldrtopicmsg": "216",
//     "ldrvaluemsg": "0",
//     "ldronoffmsg": "0",
//     "fireTopicmsg": "220",
//     "firevaluemsg": "8",
//     "fireonoffmsg": "1",
//     "fanValuemsg": "0",
//     "ledValuemsg": "0",
//     "tempTopicmsg": "214",
//     "humeTopicmsg": "215",
//     "temponoffmsg": "0",
//     "moistureTopicmsg": "201",
//     "moisturevaluemsg": "0",
//     "moistureonoffmsg": "0",
//     "ultraTopicmsg": "208",
//     "ultravaluemsg": "0",
//     "ultraonoffmsg": "0",
//     "gasTopicmsg": "211",
//     "gasvaluemsg": "0",
//     "gasonoffmsg": "0",
//     "motionTopicmsg": "205",
//     "motionvaluemsg": "0",
//     "motiononoffmsg": "0",
//     "allsensorValue1msg": "0",
//     "allsensorValue2msg": "0"
// }


// second api url:http://localhost:3000/publish 
// post method
// {
//     "topic": "smarthome/gas/control",
//     "message": "OFF"
// }



