// Define the pins connected to the ULN2003 driver
const int motorPin1 = 5;  // IN1 on ULN2003 (GPIO 5 / D1)
const int motorPin2 = 4;  // IN2 on ULN2003 (GPIO 4 / D2)
const int motorPin3 = 0;  // IN3 on ULN2003 (GPIO 0 / D3)
const int motorPin4 = 2;  // IN4 on ULN2003 (GPIO 2 / D4)

// Array to store the sequence for 4-step motor
int stepSequence[8][4] = {
  {1, 0, 0, 0}, // Step 1
  {1, 1, 0, 0}, // Step 2
  {0, 1, 0, 0}, // Step 3
  {0, 1, 1, 0}, // Step 4
  {0, 0, 1, 0}, // Step 5
  {0, 0, 1, 1}, // Step 6
  {0, 0, 0, 1}, // Step 7
  {1, 0, 0, 1}  // Step 8
};

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  
  // Set motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);

  Serial.println("Stepper Motor Control with ESP8266");
}

void loop() {
  // Rotate the motor clockwise 512 steps
  for (int i = 0; i < 512; i++) {
    stepMotor(i % 8);  // Use modulus to loop through the 8-step sequence
    delay(10);         // Delay for smooth movement (adjust as needed)
  }

  delay(1000);  // Wait for a second before reversing direction

  // Rotate the motor counterclockwise 512 steps
  for (int i = 0; i < 512; i++) {
    stepMotor(7 - (i % 8));  // Reverse the step sequence for counterclockwise
    delay(10);                // Delay for smooth movement
  }

  delay(1000);  // Wait for a second before repeating
}

void stepMotor(int step) {
  // Update motor control pins based on the current step in the sequence
  digitalWrite(motorPin1, stepSequence[step][0]);
  digitalWrite(motorPin2, stepSequence[step][1]);
  digitalWrite(motorPin3, stepSequence[step][2]);
  digitalWrite(motorPin4, stepSequence[step][3]);
}
