#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);  // Start Serial Communiation
  myservo.attach(10);      //Attach the Servo motor to pin 10
  myservo.write(90);     // Set the Angle of Motor to 90
  delay(2000);

  //Digital input pins
  pinMode(4, INPUT);  //Switch
  pinMode(7, INPUT);  //PIR Sensor Motion Sensor
  pinMode(3, INPUT);  //Push Button


  //Interrupt
  pinMode(2,INPUT_PULLUP);  //Interrupt pin 2 Pullup (Interrupt Vector 0)

  //Analog Input pins
  pinMode(A0, INPUT);  //Potentiometer
  pinMode(A1, INPUT);  //LDR

  //Digital Output
  pinMode(8, OUTPUT);  // LED On/OFF
  pinMode(9, OUTPUT);  // Relay (//operated by Motion sensor)
  pinMode(12, OUTPUT);  // DC Motor
  pinMode(13, OUTPUT);  // In Built LED
  pinMode(3, OUTPUT);  //Push Button (Pin3) Response

  //Analog Output
  pinMode(5, OUTPUT);  // pin 5 Green LED Fading // Brightness Change
  pinMode(11, OUTPUT);  //Blue LED pin 11
                           // attachInterrupt(Interrupt_Vector,ISR,Mode);
                           // MODE - RISING, FALLING, CHANGE, LOW
  //attachInterrupt(0, fire, FALLING);
  //digitalPinToInterrupt(<pin>);
  attachInterrupt(digitalPinToInterrupt(2), fire, FALLING);
}

void fire() {
  digitalWrite(12,HIGH);  //High the 12 number pin
  //ISR
}

void loop() {
  digitalWrite(13, HIGH);  //in built LED on
  delay(1000);
  digitalWrite(13, LOW);  //in built LED off
  delay(1000);
  digitalWrite(12, LOW);  //Interrupt LEd off pin 12
                                //****Check Switch On/Off***
  if (!digitalRead(4)) {
    digitalWrite(8, LOW);  //Red LED off, pin 8
    analogWrite(11, 0);   // Blue LED off,pin 11

  }
  //Switch On***********
  else {
    digitalWrite(8, HIGH);  //Red LED On ,pin 8 //System On

    //**Brightness******
    int bright = analogRead(A1);  //LDR pin A1
    Serial.println(bright);
    //    int mbright = map(bright,Low value,High Value,0,255);
    //   analogWrite(5,mbright);

    //**PotentioMeter******
    analogWrite(11, map(analogRead(A0), 0, 1023, 0, 255));//potentiometer

    //**Motion Sensor******
    /* 
      bool pir = digitalRead(7);
      Serial.println(pir);
      if(pir==1){
        digitalWrite(9,HIGH);
        delay(2000);
    	}
      else{
        digitalWrite(9,HIGH);
      	}*/
    Serial.println(digitalRead(7));
    digitalWrite(9, digitalRead(7));  // No need to turn off

    //*Servo Motor*****
    Serial.println(myservo.read());  //pin 10 sevo pin
    if (myservo.read() == 90)
      myservo.write(180);

    //**Push Button****
    bool pb = digitalRead(3);   // Normal Push Button (Pin 3)
    if (!pb) {                      //Not pb due to INPUT_PULLUP
      digitalWrite(6, HIGH);  //Led on pin 6
    } else {
      digitalWrite(6, LOW);  //Led off pin 6
    }
  }
}