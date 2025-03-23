#include <Servo.h>  // Include the Servo library

Servo myServo;  // Create a Servo object to control the servo motor

void setup() {
  // Start serial communication
  Serial.begin(115200);
  
  // Attach the servo to a pin (e.g., D5 which corresponds to GPIO 14)
  myServo.attach(14);  // GPIO 14 is connected to the servo's control pin
  
  // Print a message to indicate setup completion
  Serial.println("Servo Motor Basic Control with ESP8266");
}

void loop() {
  // Move the servo to 0 degrees
  myServo.write(0);  // Set the servo to 0 degrees
  Serial.println("Servo at 0 degrees");
  delay(1000);  // Wait for 1 second

  // Move the servo to 90 degrees
  myServo.write(90);  // Set the servo to 90 degrees
  Serial.println("Servo at 90 degrees");
  delay(1000);  // Wait for 1 second

  // Move the servo to 180 degrees
  myServo.write(180);  // Set the servo to 180 degrees
  Serial.println("Servo at 180 degrees");
  delay(1000);  // Wait for 1 second
}
