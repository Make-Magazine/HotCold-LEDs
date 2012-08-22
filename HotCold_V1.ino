// Hot/Cold LEDs v1
// using a PING))) Sensor
// Basic "hot/cold" program will blink blue until you get close, then change
// (c) 2012 julius@urgu.de

// define pins
int SensorPin=7;
int RedLedPin=5;
int BlueLedPin=6;

int distance;
unsigned long pulseDuration=0;

void setup() {}

void loop() {

  // measure distance: send "Ping"
 pinMode(SensorPin, OUTPUT);
 digitalWrite(SensorPin, HIGH);
 delayMicroseconds(5);
 digitalWrite(SensorPin, LOW);

  // measure distance: listen for "Ping"
 pinMode(SensorPin, INPUT);
 pulseDuration=pulseIn(SensorPin, HIGH);
 
 // divide by two (back/forth for a single trip), divided by speed of sound = distance in cm
 pulseDuration=pulseDuration/2; 
 distance = int(pulseDuration/29);
 
 // light up red led: inverted linear of 0-25cm to 0-255 eq. off to max. brightness
 if (distance > 0 && distance < 25) {
   int RedValue=(25-distance)*10.2;
   analogWrite(RedLedPin, RedValue); 
 } else {
   analogWrite(RedLedPin, 0);
 }
 
 // light up blue led: 0-25cm ^= 0-255, 25-50cm ^= 255-0 on BlueLedPin
 if (distance > 10 && distance <= 25) {
  int BlueValue = (distance-10)*17;
  analogWrite(BlueLedPin, BlueValue);  
 } else if (distance > 25 && distance < 50) {
  int BlueValue = (50-distance)*10.2;
  analogWrite(BlueLedPin, BlueValue);
 } else {
   analogWrite(BlueLedPin, 0);
 }
 
 // wait a little... 
 delay(20);

}

