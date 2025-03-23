#include <ESP8266WiFi.h>  // Include the ESP8266 WiFi library
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define SDA_PIN D2  /* Define the SDA pin here */
#define SCL_PIN D1  /* Define the SCL Pin here */
#define RST_PIN D3  // Reset pin connected to D1 (GPIO5)
#define SS_PIN D4   // SDA pin connected to D2 (GPIO4)
#define BUZZER D8   //buzzer
#define GREEN D0    //green led
#define BLUE D10    //blue led
#define RED D9      //red led

String uid = "";  // Global UID variable
int a;
// LiquidCrystal_I2C lcd(0x27, 16, 2);
LiquidCrystal_PCF8574 lcd(0x27);
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.

// Replace with your network cGREENentials
const char* ssid = "nk";                                           // WiFi Network Name
const char* password = "12345678";                                 // WiFi Password
const char* serverUrl = "http://192.168.77.173/Rfid/Getdata.php";  // API URL

void setup() {
  SPI.begin();                  // Initiate SPI bus.
  mfrc522.PCD_Init();           // Initialize MFRC522 RFID module.
  Wire.begin(SDA_PIN, SCL_PIN); /* Initialize I2C communication */
  lcd.begin(16, 2);
  // lcd.init();
  // lcd.backlight();
  lcd.setBacklight(255);

  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(115200);

  digitalWrite(BUZZER, LOW);
  digitalWrite(BLUE, HIGH);  // Default ON
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  wificonnecta();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Scan Your Card ");
  Serial.println("Scan your RFID tag...");
}
void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Scan Your Card");

  String uid = "";

  // Step 2: Wait for a card scan (stay in loop)
  while (uid == "" || uid == "null") {
    uid = uidscan();  // Try to get RFID UID
  }

  // Step 3: Process scanned card
  int result = sendRFIDData(uid);
  if (result != 1) {
    // If not successful, wait 10 seconds
    delay(10000);
  }

  // Go back to scanning state
}


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

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFiconnected");
  Serial.println("\nWiFi connected!");
  delay(2000);
  lcd.clear();


  lcd.setCursor(0, 0);
  lcd.print("IP: ");
  lcd.setCursor(3, 1);
  lcd.print(WiFi.localIP());
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Print the local IP address
  delay(1000);
  // lcd.clear();
}
String uidscan() {
  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print(" Scan your Card ");
  // lcd.clear();

  if (!mfrc522.PICC_IsNewCardPresent()) { return ""; }
  /* Select one of the cards */
  if (!mfrc522.PICC_ReadCardSerial()) { return ""; }
  /* Read data from the same block */

  Serial.println("UID of the tag is: ");
  // Print the UID of the card.
  // lcd.setCursor(0, 1);
  String scannedUID = "";

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    scannedUID += String(mfrc522.uid.uidByte[i], HEX);

    // Serial.print("");
  }
  //  lcd.print(scannedUID);
  Serial.println(scannedUID);

  mfrc522.PICC_HaltA();  // Halt the current card.
  mfrc522.PCD_StopCrypto1();
  // Stop encryption on the card.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Checking...");
  return scannedUID;
  // // Keep the loop empty for basic WiFi connection

  // delay(1000);
}
int sendRFIDData(String uid) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    // WiFiClientSecure client;
    // client.setInsecure(); // Ignore SSL certificate validation
    // http.begin(client, serverUrl);

    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Create JSON object
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["uid"] = uid;

    String requestBody;
    serializeJson(jsonDoc, requestBody);

    Serial.println("Sending request: " + requestBody);

    int httpResponseCode = http.POST(requestBody);

    if (httpResponseCode > 0) {
      Serial.println("Response received");
      String response = http.getString();
      Serial.println("Raw Response: " + response);

      // Parse JSON response
      StaticJsonDocument<200> responseDoc;
      DeserializationError error = deserializeJson(responseDoc, response);

      if (!error) {
        int statusCode = responseDoc["status_code"];
        String message1 = responseDoc["message1"];
        String message2 = responseDoc["message2"];

        Serial.println("Status Code: " + String(statusCode));
        Serial.println("Message1: " + message1);
        Serial.println("Message2: " + message2);

        if (statusCode == 200) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(message1);
          lcd.setCursor(0, 1);
          lcd.print(message2);

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

        } else if (statusCode == 301) {
          lcd.setCursor(0, 0);
          lcd.print(message2);

          digitalWrite(RED, HIGH);
          digitalWrite(BUZZER, HIGH);
          delay(1000);
          digitalWrite(BUZZER, LOW);
          digitalWrite(RED, LOW);

          delay(1000);

          lcd.clear();
        } else {
          lcd.setCursor(0, 0);
          lcd.print(message1);
          lcd.setCursor(0, 1);
          lcd.print(message2);
        }


      } else {
        Serial.println("JSON Parsing Failed!");
      }
    } else {
      Serial.print("HTTP Request Failed, Error: ");
      Serial.println(httpResponseCode);
      Serial.print("HTTP Request Failed, Error: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());  // Print detailed error
    }

    http.end();
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi not connect");
    Serial.println("WiFi not connected!");
  }

  return 1;
}
