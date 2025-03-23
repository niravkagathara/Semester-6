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

const char* ssid = "nk";
const char* password = "12345678";
const char* serverUrl = "http://192.168.51.173/Rfid/Getdata.php";  

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
  // Serial.print("\nConnecting");

  lcd.begin(16, 2);
  lcd.setBacklight(255);
  delay(500);
  pinMode(BUZZER, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(115200);

  digitalWrite(BUZZER, LOW);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(RED, LOW);

  connectToWiFi();
  showMessage("Scan Your Card");
}
void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String uid = getRFIDUID();
    if (!uid.isEmpty()) {
      processRFID(uid);
      delay(2000); // 🕒 Add delay to prevent server overload
    }
  }
}


void connectToWiFi() {
  showMessage("Connecting to WiFi...");
  

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  // int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
    // retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi Connected!");
    showMessage("WiFi Connected", WiFi.localIP().toString());
    delay(2000);
  } else {
    Serial.println("\nWiFi Failed!");
    showMessage("WiFi Failed", "Check Config!");
    delay(5000);
  }
}

String getRFIDUID() {
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  Serial.println("Scanned UID: " + uid);
  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();  

  return uid;
}

void processRFID(String uid) {
  int result = sendRFIDData(uid);
  if (result == 1) {
    Serial.println("RFID Processed Successfully!");
  }
}

int sendRFIDData(String uid) {
  if (WiFi.status() != WL_CONNECTED) {
    showMessage("WiFi Lost", "Reconnecting...");
    connectToWiFi();
    return 0;
  }

  HTTPClient http;
   WiFiClient client;  
  // WiFiClientSecure  client;
  // client.setInsecure();  // Disable SSL certificate verification

  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/json");
    // http.setTimeout(10000);  // Increase timeout

  StaticJsonDocument<200> jsonDoc;
  jsonDoc["uid"] = uid;
  String requestBody;
  serializeJson(jsonDoc, requestBody);
  // delay(500);  // Add delay before making another reques
  Serial.println("Sending: " + requestBody);
  int httpResponseCode = http.POST(requestBody);
  if (httpResponseCode <= 0) {
    Serial.println("HTTP Error: " + String(httpResponseCode));
    http.end();
    return 0;
  }

  String response = http.getString();
  Serial.println("Response: " + response);
  http.end();  
  // delay(1000);  // Small delay to prevent rapid API calls

  StaticJsonDocument<200> responseDoc;
  DeserializationError error = deserializeJson(responseDoc, response);
  // http.end();

  if (error) {
    Serial.println("JSON Parse Error!");
    return 0;
  }

  int statusCode = responseDoc["status_code"];
  String message1 = responseDoc["message1"];
  String message2 = responseDoc["message2"];

  Serial.println("Status: " + String(statusCode));
  Serial.println("Msg1: " + message1);
  Serial.println("Msg2: " + message2);

  if (statusCode == 200) {
    showMessage(message1, message2);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(GREEN, LOW);
    digitalWrite(BUZZER, LOW);
  } else {
    showMessage("Access Denied", message2);
    digitalWrite(RED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);
  }

  delay(1000);
  showMessage("Scan Your Card");  // Ensure LCD resets for the next scan
  return 1;
}
