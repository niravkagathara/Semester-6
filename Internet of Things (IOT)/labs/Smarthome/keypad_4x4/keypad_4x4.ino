// Include necessary libraries
#include <Wire.h>
#include <PCF8574.h>
#include <Servo.h>

// Define PCF8574 address
PCF8574 pcf8574(0x20);  // Change address if needed

// Define Servo object
Servo servo;

// Define password
String correctPassword = "1234";
String enteredPassword = "";

// Define pins
#define SERVO_PIN D5     // Servo motor connected to D5 of ESP8266
#define SDA_PIN D2       // I2C SDA pin connected to D2 of ESP8266
#define SCL_PIN D1       // I2C SCL pin connected to D1 of ESP8266

unsigned long unlockTime = 0;
const unsigned long unlockDuration = 5000;  // 5 seconds unlock period
bool doorUnlocked = false;

void setup() {
  Serial.begin(9600);
  Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I2C with defined pins
  pcf8574.begin();

  servo.attach(SERVO_PIN);
  servo.write(0);  // Initial position (Locked)

  Serial.println("Enter Password:");
}

char readKeypad() {
  for (int i = 0; i < 8; i++) {
    pcf8574.write(i, LOW);
    for (int j = 0; j < 4; j++) {
      if (!pcf8574.read(j + 4)) {
        while (!pcf8574.read(j + 4));  // Wait for release
        char keys[4][4] = {
          {'1', '2', '3', 'A'},
          {'4', '5', '6', 'B'},
          {'7', '8', '9', 'C'},
          {'*', '0', '#', 'D'}
        };
        return keys[j][i];
      }
    }
    pcf8574.write(i, HIGH);
  }
  return '\0';  // Return null character if no key is pressed
}

void loop() {
  char key = readKeypad();
  unsigned long currentMillis = millis();

  if (key != '\0') {
    Serial.print(key);

    if (key == '#') {  // Check password when '#' is pressed
      if (enteredPassword == correctPassword) {
        Serial.println("\nPassword Correct! Door Unlocked.");
        servo.write(90);  // Open door
        unlockTime = currentMillis;
        doorUnlocked = true;
      } else {
        Serial.println("\nIncorrect Password. Try Again.");
      }
      enteredPassword = "";  // Reset entered password
      Serial.println("Enter Password:");
    } 
    else if (key == '*') {  // Clear entered password when '*' is pressed
      enteredPassword = "";
      Serial.println("\nPassword Cleared. Enter Password Again:");
    }
    else {
      enteredPassword += key;  // Append key to entered password
    }
  }

  // Check if door should be locked again
  if (doorUnlocked && (currentMillis - unlockTime >= unlockDuration)) {
    servo.write(0);    // Lock door again
    doorUnlocked = false;
    Serial.println("Door Locked.");
  }
}


// #include <Wire.h>
// #include <Keypad_I2C.h>
// #include <Keypad.h>

// #define I2C_ADDR 0x20  // Your PCF8574 I2C address
// Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2C_ADDR);

// // Define the size of the keypad
// const byte ROWS = 4; // Four rows
// const byte COLS = 4; // Four columns

// // Define the key map
// char keys[ROWS][COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'}
// };

// // Password-related variables
// String enteredPassword = "";
// String correctPassword = "1234";  // Set your desired password here

// void setup() {
//   Serial.begin(115200);
//   Wire.begin(D2, D1); // SDA, SCL
//   keypad.begin(makeKeymap(keys));
//   Serial.println("Enter Password: ");
// }

// void loop() {
//   char key = keypad.getKey();

//   if (key) {
//     if (key == 'C') {       // Clear Password
//       enteredPassword = "";
//       Serial.println("Password Cleared.");
//     } 
//     else if (key == 'D') {  // Submit Password
//       if (enteredPassword == correctPassword) {
//         Serial.println("Password Correct!");
//       } else {
//         Serial.println("Wrong Password.");
//       }
//       enteredPassword = ""; // Clear entered password after checking
//     } 
//     else {  // Append key to password
//       enteredPassword += key;
//       Serial.print("*");  // Display * instead of the actual key
//     }
//   }
// }

// #include <Keypad.h>

// // Keypad Configuration
// const byte ROWS = 4;
// const byte COLS = 4;

// char keys[ROWS][COLS] = {
//   {'1', '2', '3', 'A'},
//   {'4', '5', '6', 'B'},
//   {'7', '8', '9', 'C'},
//   {'*', '0', '#', 'D'}
// };

// // Define row and column pins connected to the keypad
// byte rowPins[ROWS] = {D1, D2, D3, D4};    // R1, R2, R3, R4
// byte colPins[COLS] = {D5, D6, D7, D8};    // C1, C2, C3, C4

// // Create keypad object
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// void setup() {
//   Serial.begin(9600);
//   Serial.println("4x4 Keypad Test - Ready to Receive Input");
// }

// void loop() {
//   char key = keypad.getKey();

//   if (key) {
//     Serial.print("Key Pressed: ");
//     Serial.println(key);
//   }
// }
