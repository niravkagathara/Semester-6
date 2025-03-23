#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D2   // Reset pin for ESP8266
#define SS_PIN D8    // Slave Select pin for ESP8266

MFRC522 rfid(SS_PIN, RST_PIN); // Create MFRC522 instance

void setup() {
  Serial.begin(9600);  // Start Serial Monitor with matching baud rate
  SPI.begin();           // Initialize SPI bus
  rfid.PCD_Init();       // Initialize RFID reader

  Serial.println("Place an RFID tag near the reader...");
}

void loop() {
  // Check if a new card is present
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Check if the card can be read
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Print the UID
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "); // Format for readability
    Serial.print(rfid.uid.uidByte[i], HEX);               // Print in hexadecimal
  }
  Serial.println();

  // Halt the card
  rfid.PICC_HaltA();
	delay(1000);
}
