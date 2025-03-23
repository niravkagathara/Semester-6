#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define SDA_PIN D2
#define SCL_PIN D1
#define RST_PIN D3
#define SS_PIN D4

#define BUZZER D8
#define GREEN D0
#define BLUE D10
#define RED D9


LiquidCrystal_PCF8574 lcd(0x27);
MFRC522 mfrc522(SS_PIN, RST_PIN);

const char* ssid = "nk";            // Replace with your WiFi SSID
const char* password = "12345678";  // Replace with your WiFi password

const char* serverUrl = "http://192.168.51.173/Rfid/Getdata.php";  // API URL

void showMessage(String line1, String line2 = "") {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}
void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  Wire.begin(SDA_PIN, SCL_PIN);

  lcd.begin(16, 2);
  lcd.setBacklight(255);
  delay(500);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);
  Serial.begin(115200);
  connectToWiFi();
  showMessage("Scan Your Card");

  // sendRFIDData("abcaaaa");  // Replace "abc" with actual RFID UID
}

void loop() {
  // Do nothing in loop
  String uid=getRFIDUID();
  if (!uid.isEmpty()) {
      sendRFIDData(uid);
      delay(2000); // 🕒 Add delay to prevent server overload
    }
  // sendRFIDData("abc");
  // delay(2000);
}

void connectToWiFi() {
  showMessage("Connecting to ", "WiFi...");
  WiFi.begin(ssid, password);
  Serial.print("Connecting");


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    // showMessage("",".");
  }


  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    showMessage("WiFi Connected", WiFi.localIP().toString());
    delay(500);
  } else {
    Serial.println("\nWiFi Failed!");
    showMessage("WiFi Failed", "Check Config!");
    delay(500);
  }
}
String getRFIDUID() {
  String uid = "";
   if (!mfrc522.PICC_IsNewCardPresent()) { return ""; }
  /* Select one of the cards */
  if (!mfrc522.PICC_ReadCardSerial()) { return ""; }
  /* Read data from the same block */

  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.println("Scanned UID: " + uid);
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();  
  // delay(1000);
  return uid;
}
void sendRFIDData(String uid) {
  showMessage("Checking..");

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    WiFiClient client;
    // WiFiClientSecure client;
    // client.setInsecure(); // Ignore SSL certificate validation
    // http.begin(client, serverUrl);

    http.begin(client, serverUrl);
    http.addHeader("Content-Type", "application/json");
    http.setTimeout(30000);  // Increase timeout

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
          showMessage(message1, message2);
          digitalWrite(GREEN, HIGH);
          digitalWrite(BUZZER, HIGH);
          delay(200);
          digitalWrite(GREEN, LOW);
          digitalWrite(BUZZER, LOW);
          delay(1000);

        } else {
          showMessage("Access Denied", message2);
          digitalWrite(RED, HIGH);
          digitalWrite(BUZZER, HIGH);
          delay(1000);
          digitalWrite(RED, LOW);
          digitalWrite(BUZZER, LOW);
          delay(1000);
        }
                showMessage("Scan Your Card");  // Ensure LCD resets for the next scan

      } else {
        Serial.println("JSON Parsing Failed!");
      }

    } else {
      if (httpResponseCode == -11) {
        showMessage("ReScan Your Card");
      } else if (httpResponseCode == -1) {
        showMessage("ReScan Your Card");
      }
      Serial.print("HTTP Request Failed, Error: ");
      Serial.println(httpResponseCode);
      Serial.print("HTTP Request Failed, Error: ");
      Serial.println(http.errorToString(httpResponseCode).c_str());  // Print detailed error
      http.end();
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
    showMessage("WiFi Lost", "Reconnecting...");
    connectToWiFi();
  }
}
