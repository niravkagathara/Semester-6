#define TRIG_PIN D5 // GPIO14
#define ECHO_PIN D6 // GPIO12

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Ultrasonic Sensor Test");

  // Set TRIG as OUTPUT and ECHO as INPUT
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
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

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(1000); // Delay for readability
}