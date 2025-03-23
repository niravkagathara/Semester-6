int Upper Threshold = 518;
int Lower Threshold = 490;
int reading = 0;
float BPM = 0.0;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long Second PulseTime = 0;
unsigned long PulseInterval = 0;
void setup(){
Serial.begin(9600);
}
void loop() {
  reading analogRead(A0);
  if (reading > Upper Threshold && IgnoreReading == false) {
    if (FirstPulseDetected false) {
      FirstPulseTime = millis();
      FirstPulseDetected = true;
    } else {

      SecondPulseTime = millis();
      PulseInterval = Second PulseTime - FirstPulseTime;
      FirstPulseTime = SecondPulseTime;
    }
    IgnoreReading = true;
  }
  if (reading < Lower Threshold) {
    IgnoreReading = false;
  }  //Hear beat trailing edge detection
  BPM = (1.0 / PulseInterval) * 60.0 * 1000;
    Serial.print(BPM);
    Serial.println(" BPM");
    Serial.flush();
}