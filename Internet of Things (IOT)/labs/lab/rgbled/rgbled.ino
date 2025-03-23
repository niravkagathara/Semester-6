#define RED_PIN   D9  // GPIO5
#define GREEN_PIN D0  // GPIO4
#define BLUE_PIN  D10  // GPIO14

void setup() {
    pinMode(RED_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
    // Cycle through different colors
    setColor(255, 0, 0); // Red
    delay(1000);
    setColor(0, 255, 0); // Green
    delay(1000);
    setColor(0, 0, 255); // Blue
    delay(1000);
    setColor(255, 255, 0); // Yellow
    delay(1000);
    setColor(0, 255, 255); // Cyan
    delay(1000);
    setColor(255, 0, 255); // Magenta
    delay(1000);
    setColor(255, 255, 255); // White
    delay(1000);
    setColor(0, 0, 0); // OFF
    delay(1000);
}

// Function to set RGB LED color using PWM
void setColor(int red, int green, int blue) {
    analogWrite(RED_PIN, red);  
    analogWrite(GREEN_PIN, green);  
    analogWrite(BLUE_PIN, blue);  
}
