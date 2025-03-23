// C++ code
//
void setup()
{
  pinMode(5, INPUT);
  pinMode(10, OUTPUT);
 	Serial.begin(9600);
  Serial.println("hello");
  delay(1000);
}

void loop()
{
  bool ssb= digitalRead(5);
  int ssi=digitalRead(5);
    Serial.println(ssb);
    Serial.println("*******************");
    Serial.println(ssi);
	if(ssi==1)
  		digitalWrite(10, HIGH);
	else
  		digitalWrite(10, LOW);

}