#include <ESP8266WiFi.h>  // Include the ESP8266 WiFi library
#include <Wire.h>
// #include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_PCF8574.h>
#include <SPI.h>
#include <MFRC522.h>

#define SDA_PIN D2  /* Define the SDA pin here */
#define SCL_PIN D1  /* Define the SCL Pin here */
#define RST_PIN D3  // Reset pin connected to D1 (GPIO5)
#define SS_PIN D4   // SDA pin connected to D2 (GPIO4)
#define BUZZER D8
#define GREEN D0
#define BLUE D10
#define RED D9


// LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_PCF8574 lcd(0x27);
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

// Replace with your network cGREENentials
const char* ssid = "nk";            // WiFi Network Name
const char* password = "12345678";  // WiFi Password
void wificonnecta() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("  Initializing  ");
  Serial.println("\nConnecting to WiFi...");

  WiFi.begin(ssid, password);  // Connect to WiFi network
  lcd.setCursor(0, 1);

  while (WiFi.status() != WL_CONNECTED) {  // Wait for connection
    delay(500);
    Serial.print(".");
    lcd.print(".");
  }
  lcd.setCursor(0, 0);
  lcd.print("WiFiconnected");
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("IP address: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  Serial.println("\nWiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address
  lcd.clear();
}
void uidscan() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Scan your Card ");
  // lcd.clear();

  if (!mfrc522.PICC_IsNewCardPresent()) { return; }
  /* Select one of the cards */
  if (!mfrc522.PICC_ReadCardSerial()) { return; }
  /* Read data from the same block */

  Serial.println("UID of the tag is: ");
  // Print the UID of the card.
  lcd.setCursor(0, 1);
      String uid = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
        uid += String(mfrc522.uid.uidByte[i], HEX);
   
    // Serial.print("");
  }
   lcd.print(uid);
    Serial.println(uid);


  mfrc522.PICC_HaltA();       // Halt the current card.
  mfrc522.PCD_StopCrypto1(); 
   // Stop encryption on the card.
     lcd.clear();

    if(uid=="be7f332"){
    lcd.setCursor(0,0);
    lcd.print("    present    ");
    lcd.setCursor(0,1);
    lcd.print(uid);
    
    digitalWrite(BUZZER, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);

    delay(200);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, LOW);
    digitalWrite(BLUE, HIGH);

  // delay(200);
  // digitalWrite(BUZZER, HIGH);
  // delay(200);
  // digitalWrite(BUZZER, LOW);
  // delay(200);
  // digitalWrite(GREEN, HIGH);
  // delay(200);
  // digitalWrite(GREEN, LOW);
            delay(1000);

    lcd.clear();

  }
  else{
    lcd.setCursor(0,0);
    lcd.print(" access  decied ");
  digitalWrite(RED, HIGH);
   digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(BUZZER, LOW);
    digitalWrite(RED, LOW);

        delay(1000);

  lcd.clear();

  }
  // Keep the loop empty for basic WiFi connection

      delay(1000);

}
void setup() {


  Wire.begin(SDA_PIN, SCL_PIN); /* Initialize I2C communication */
  lcd.begin(16, 2);

  // lcd.init();
  // lcd.backlight();
  lcd.setBacklight(255);
    Serial.begin(9600);

  wificonnecta();
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();  // Initialize MFRC522 RFID module.
                       // Initiate SPI bus.
  Serial.println("Scan your RFID tag...");
}

void loop() {
  digitalWrite(BLUE, HIGH);
  uidscan();

}
