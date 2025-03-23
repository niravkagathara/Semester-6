//ardiuno uno sent message basic message hello
void setup() {
    Serial.begin(9600);  // Hardware Serial
}

void loop() {
    Serial.println("Hello from Arduino!");  // Send data
    delay(2000);
}
