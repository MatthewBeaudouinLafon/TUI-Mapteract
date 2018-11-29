int clockPin = 9;
int dataPin = 12;
int latchPin = 11;
byte switches = 0;

void (*switchResponses[8])();

void age1() {
  // Turn off attractions unsuitable for 5-14 year olds
  Serial.println("Turning off place not for 5-14 year olds");
}

void age2() {
  // Turn off attractions unsuitable for 15-24 year olds
  Serial.println("Turning off place not for 15-24 year olds");
}

void age3() {
  // Turn off attractions unsuitable for 25+ year olds
  Serial.println("Turning off place not for 25+ year olds");
}

void height() {
  // Turn off attractions with a 4ft requirement
  Serial.println("Turning off attractions with a 4ft requirement");
}

void time5() {
  // Turn off 5 minute attractions
  Serial.println("Turning off 5 minute attractions");
}

void time10() {
  // Turn off 10 minute attractions
  Serial.println("Turning off 10 minute attractions");
}

void time15() {
  // Turn off 15 minute attractions
  Serial.println("Turning off 15 minute attractions");
}

void water() {
  // Turn off water rides
  Serial.println("Turning off water rides");
}

void setup() {
  //start serial
  Serial.begin(9600);

  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);

  switchResponses[0] = age1;
  switchResponses[1] = age2;
  switchResponses[2] = age3;
  switchResponses[3] = height;
  switchResponses[4] = time5;
  switchResponses[5] = time10;
  switchResponses[6] = time15;
  switchResponses[7] = water;
}

byte updateShiftRegisterIn(){
  //Pulse the latch pin:
  //set it to 1 to collect parallel data
  digitalWrite(latchPin, HIGH);
  //set it to 1 to collect parallel data, wait
  delayMicroseconds(20);
  //set it to 0 to transmit data serially  
  digitalWrite(latchPin, HIGH);

  return shiftIn(dataPin, clockPin, MSBFIRST);
}

void loop() {
  switches = updateShiftRegisterIn();
  Serial.println(switches, BIN);

  interpretSwitches();
}

void interpretSwitches() {
  for (int n=0; n<=7; n++)
  {
    if (switches & (1 << n) ){ // True if nth bit is 1
      switchResponses[n];
    }
  }
}
