// Hot/Cold LEDs v2
// using a PING))) Sensor
// Try and "capture the ping" when the Red LED blinks - if you win, Red LED will flash; if you lose or cheat, Blue LED will flash
// (c) 2012 julius@urgu.de

int SensorPin=7; int RedLedPin=5; int BlueLedPin=6;
unsigned long timer; unsigned long distance=0; boolean gotIt;

void setup() {  Serial.begin(9600); }

void loop() {

  // turn on blue LED
  analogWrite(BlueLedPin, 255);
  
  // seed the random generator and wait a random time
  randomSeed(analogRead(1));
  delay(random(2000,19000));
  
  // turn off blue LED, turn on red
  analogWrite(BlueLedPin, 0);
  analogWrite(RedLedPin, 255);
  
  // loop of measurements start here
  
  timer=millis();
  gotIt = false;
  distance=0;

 do  {
   
 // measure distance: send "Ping"
  pinMode(SensorPin, OUTPUT);
  digitalWrite(SensorPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(SensorPin, LOW);
 // measure distance: listen for "Ping"
  pinMode(SensorPin, INPUT);
  distance=pulseIn(SensorPin, HIGH, 870);
 // got it?
  if (distance > 0 && distance<870) { gotIt = true; } 
 // dim red led
 analogWrite(RedLedPin, (255-((millis()-timer)/2)) );
 
 } while ( (millis()-timer) < 500 && gotIt == false );

  // either time is up, or gotIt - red LED off
  analogWrite(RedLedPin, 0);

  // blink red for win, blue for loose
  // not only check for gotIt, if too short assume cheating (hand in front of sensor)
   if ( gotIt == true && (millis()-timer) > 10 ) {

     // print reaction time to serial interface
    Serial.print("Your reaction time was ");
    Serial.print(millis()-timer);
    Serial.println(" ms");
 
     for (int i=0; i <= 5; i++) {
      analogWrite(RedLedPin, 255); delay(200);
      analogWrite(RedLedPin, 0); delay(200);
      
      
     } 
   } else { 
    for (int i=0; i <= 5; i++) {
      analogWrite(BlueLedPin, 255); delay(200);
      analogWrite(BlueLedPin, 0); delay(200);
     } 
   }
// end main loop   
}
