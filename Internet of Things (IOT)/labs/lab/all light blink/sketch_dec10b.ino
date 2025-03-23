// C++ code
//
// C++ code
//
void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

}

void loop()
{
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)

  digitalWrite(9, LOW);
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}