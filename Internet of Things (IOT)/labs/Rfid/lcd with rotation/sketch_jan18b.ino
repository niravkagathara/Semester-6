#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN D6 /* Define the SDA pin here */ 
#define SCL_PIN D7 /* Define the SCL Pin here */

LiquidCrystal_I2C lcd(0x27, 16, 2);

String message = "www.ElectronicWings.com";

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);  /* Initialize I2C communication */
  lcd.init();
  lcd.backlight();
 
}

void loop() {
lcd.print(message);

While(1){
  lcd.scrollDisplayLeft(); /* Scroll the display to the left */
  delay(500);  /* delay according to scrolling speed you want*/
}
}