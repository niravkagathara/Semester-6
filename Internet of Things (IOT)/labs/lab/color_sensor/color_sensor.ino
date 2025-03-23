#define so 9
#define s1 8
#define s2 11
#define s3 12
#define out 10
int frequency = 0;
void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  Serial.begin(9600);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}
void loop() {
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(out, LOW);
  frequency = map(frequency, 30, 90, 255, 0);
  Serial.print("G = ");
  Serial.print(frequency);
  Serial.print("\t");
  delay(100);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(out, LOW);
  frequency = map(frequency, 25, 70, 255, 0);
  Serial.print("B = ");
  Serial.print(frequency);
  Serial.print("\t");
  delay(100);
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  frequency = pulseIn(out, LOW);
  frequency = map(frequency, 10, 56, 255, 0);
  Serial.print("R = ");
  Serial.print(frequency);
  Serial.print("\t");
  delay(100);
}