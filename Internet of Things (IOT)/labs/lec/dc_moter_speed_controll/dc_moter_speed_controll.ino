// Define pins connected to L298N Motor Driver
const int motorPin1 = 5;   // IN1 on L298N (GPIO 5 / D1)
const int motorPin2 = 4;   // IN2 on L298N (GPIO 4 / D2)
const int motorSpeedPin = 12; // ENA on L298N (GPIO 12 / D6)

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Set motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorSpeedPin, OUTPUT);
  
  // Print a message indicating that the motor control has started
  Serial.println("DC Motor Speed Control with ESP8266");
}

void loop() {
  // Rotate motor clockwise with 50% speed
  digitalWrite(motorPin1, HIGH);  // Set IN1 HIGH
  digitalWrite(motorPin2, LOW);   // Set IN2 LOW
  analogWrite(motorSpeedPin, 128); // Set speed (0-255, 128 is 50% speed)
  Serial.println("Motor rotating clockwise at 50% speed");
  delay(2000); // Wait for 2 seconds

  // Rotate motor counterclockwise with 75% speed
  digitalWrite(motorPin1, LOW);   // Set IN1 LOW
  digitalWrite(motorPin2, HIGH);  // Set IN2 HIGH
  analogWrite(motorSpeedPin, 191); // Set speed (191 is ~75% speed)
  Serial.println("Motor rotating counterclockwise at 75% speed");
  delay(2000); // Wait for 2 seconds

  // Stop the motor
  digitalWrite(motorPin1, LOW);   // Set IN1 LOW
  digitalWrite(motorPin2, LOW);   // Set IN2 LOW
  analogWrite(motorSpeedPin, 0);  // Stop the motor
  Serial.println("Motor stopped");
  delay(2000); // Wait for 2 seconds
}
