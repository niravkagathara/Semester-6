#define PIR_PIN D0  // PIR sensor connected to GPIO5 (D1) on NodeMCU ESP8266
#define LED_PIN D1  // LED connected to GPIO0 (D3) on NodeMCU ESP8266

int motionCount = 0;
bool motionDetectedPreviously = false;
unsigned long ledOnTime = 0; // Store the time when LED was turned on
bool ledState = false; // Track LED state

void setup() {
  Serial.begin(115200);
  Serial.println("Motion Detector Initializing...");

  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW); // Start with LED off
}

void loop() {
  int motionDetected = digitalRead(PIR_PIN);

  if (motionDetected == HIGH && !motionDetectedPreviously) {
    motionCount++;
    Serial.print("Motion Count: ");
    Serial.println(motionCount);

    if (motionCount == 1) {
      digitalWrite(LED_PIN, HIGH); // Turn on LED at first detection
      Serial.println("LED ON (Motion Detected)");
      ledOnTime = millis(); // Record the time LED was turned on
      ledState = true;
    } 
    if(motionCount>1){
        ledOnTime = millis(); // Record the time LED was turned on
      ledState = true;
    }

    motionDetectedPreviously = true; // Mark motion as detected
  } else if (motionDetected == LOW) {
    motionDetectedPreviously = false; // Reset motion detection state
  }

  // Turn off LED after 10 seconds if it was turned on
  if (ledState && millis() - ledOnTime >= 10000) {
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF (10 seconds elapsed)");
    motionCount = 0; // Reset count
    ledState = false;
  }
}