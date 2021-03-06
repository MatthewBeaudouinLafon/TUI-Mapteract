int dataPin = 9;
int clockPin = 7;
int latchPin = 8;
byte switches = 72;

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

byte updateShiftRegisterIn(){
  digitalWrite(latchPin, HIGH);
  delayMicroseconds(20); 
  digitalWrite(latchPin, LOW);

  switches = shiftIn(dataPin, clockPin);
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

void loop() {
  Serial.println(switches, BIN);
  updateShiftRegisterIn();

  interpretSwitches();
  delay(500);
}

void interpretSwitches() {
  for (int n=0; n<=7; n++)
  {
    if (switches & (1 << n) ){ // True if nth bit is 1
      (switchResponses[n])();
    }
  }
}

byte shiftIn(int myDataPin, int myClockPin) { 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);

  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(0.2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else {
      //turn it off -- only necessary for debuging
     //print statement since myDataIn starts as 0
      pinState = 0;
    }

    digitalWrite(myClockPin, 1);

  }
  return myDataIn;
}
