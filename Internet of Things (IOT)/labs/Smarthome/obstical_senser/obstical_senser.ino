// //Rudra DIY Crafts 
// //Blynk Alert system

// // #define BLYNK_TEMPLATE_ID "TMPL3M_H-R489"
// // #define BLYNK_TEMPLATE_NAME "Obstacle"
// // #define BLYNK_AUTH_TOKEN "GOTAB8qSmuqAw4h9eqM8gxJHcAGyt99q"

// // #define BLYNK_PRINT Serial
// #include <ESP8266WiFi.h>
// // #include <BlynkSimpleEsp8266.h>

// // BlynkTimer timer;

// // char auth[] = BLYNK_AUTH_TOKEN; //Auth code sent via Email
// // char ssid[] = "vivek"; //Wifi name
// // char pass[] = "password";  //Wifi Password
// int flag=0;
// int irPin = D1;
// int buzzPin = D3;

// void notifyOnThings()
// {
//   int isIRsensed = digitalRead(irPin);
//   if (isIRsensed==1 && flag==0) {
//     Serial.println("FIRE ALERT");
//     digitalWrite(buzzPin,HIGH);
//     // Blynk.notify("Alert : FIRE ALERT");
//     flag=1;
//   }
//   else if (isIRsensed==0)
//   { 
//     digitalWrite(buzzPin,LOW);
//     flag=0;
//   }
// }
// void setup()
// {
// Serial.begin(9600);
// // Blynk.begin(auth, ssid, pass); 
// pinMode(buzzPin,OUTPUT);
// pinMode(irPin,INPUT_PULLUP);
// // timer.setInterval(1000L,notifyOnThings); 
// }
// void loop()
// {
//   int isIRsensed = digitalRead(irPin);
//   if (isIRsensed==1 && flag==0) {
//     Serial.println("FIRE ALERT");
//     digitalWrite(buzzPin,HIGH);
//     // Blynk.notify("Alert : FIRE ALERT");
//     flag=1;
//   }
//   else if (isIRsensed==0)
//   { 
//     digitalWrite(buzzPin,LOW);
//     flag=0;
//   }
//   // Blynk.run();
//   // timer.run();
// }

// Define pins
#define PIR_PIN D1
#define LED_PIN D3

void setup() {
  // Initialize serial monitor
  Serial.begin(9600);
  Serial.println("Motion Detector Initializing...");

  // Initialize PIR sensor and LED
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Start with LED off
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // Read the PIR sensor state
  int motionDetected = digitalRead(PIR_PIN);

  if (motionDetected == LOW) {
    Serial.println("Motion Detected!");
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    // delay(1000);                // Keep LED on for 2 seconds
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }

  delay(100); // Small delay for stability
}
