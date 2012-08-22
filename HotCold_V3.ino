
// Hot/Cold LEDs v3
// using a PING))) Sensor
// glows blue when away from Sensor, stays solid red when in front of Sensor;
// code below will also wake up sleeping POSIX (Linux, Mac) computers
// (c) 2012 julius@urgu.de

int usbChipPin=12;
int SensorPin=7;
int BlueLedPin=6;
int RedLedPin=5;
int counter=0;
int resetCounter=0;
int ledState=1;
int ledDirection=1;
boolean isSend=false;
unsigned long pulseDuration=0;


void setup() {
  // make led pin ready
  pinMode(BlueLedPin, OUTPUT);
  // make wake up pin ready
  pinMode(12, INPUT);  
}

void loop() {

  // make led light steady while sensing, or dim led while idle
  if (counter>0 && isSend == false) {
    analogWrite(BlueLedPin, 200);
  } else if (isSend == false) {
    if (ledDirection == 1) {
      analogWrite(BlueLedPin, ledState);
      if (ledState == 125) { ledDirection=-1; } else { ledState = ledState + 1; }
    } else {
      analogWrite(BlueLedPin, ledState);
      if (ledState < 1) { ledDirection=1; } else { ledState = ledState - 1; }
    } 
  } else {
    analogWrite(RedLedPin, 255);
    analogWrite(BlueLedPin, 0);
  }
  
   // measure distance: send "Ping"
   pinMode(SensorPin, OUTPUT);
   digitalWrite(SensorPin, HIGH);
   delayMicroseconds(5);
   digitalWrite(SensorPin, LOW);

   // measure distance: listen for "Ping"
   pinMode(SensorPin, INPUT);
   pulseDuration=pulseIn(SensorPin, HIGH);
 
   // if someone is in reach, count up, or reset if not
   if ( pulseDuration < 10000 ) {
     counter = counter + 1;
     if (counter > 50) { resetCounter=0; }
   } else { 
     resetCounter = resetCounter +1; 
       if (resetCounter > 100) {
       counter=0;
       resetCounter=0;
       isSend=false;
       analogWrite(RedLedPin, 0);
       }
   }  
 
  // if someone is there for 300 loops, start up pc 
  if (isSend == false && counter > 100) {
  // reset usb-to-serial chip
  pinMode(usbChipPin, OUTPUT);
  digitalWrite(usbChipPin, LOW);
  delay(250);
  pinMode(12, INPUT);  
  // don't do it again
  isSend=true;
  }
  
  delay(10);
}
