int dataPin = 11;
int clockPin = 12;
int latchPin = 8;
byte ledStatesTop = 255;
byte ledStatesBottom = 255;

int loopIterator = 0;

void (*switchResponses[8])();

// Clears led at a certain number. Handles top vs bottom led.
void clearLed(int ledNum) {
  if (ledNum < 8) {
    bitClear(ledStatesTop, ledNum);
  } else if (ledNum < 16) {
    bitClear(ledStatesBottom, ledNum - 8);
  } else {
    Serial.print("ledNum = ");
    Serial.print(ledNum);
    Serial.println(" is invalid.");
  }
}

void resetLeds() {
  ledStatesTop = 255;
  ledStatesBottom = 255;
}

void age1() {
  // Turn off attractions unsuitable for 5-14 year olds
  Serial.println("Turning off place not for 5-14 year olds");
  clearLed(4);
  clearLed(8);
  clearLed(2);
  clearLed(14);
}

void age2() {
  // Turn off attractions unsuitable for 15-24 year olds
  Serial.println("Turning off place not for 15-24 year olds");
  clearLed(2);
  clearLed(14);
  clearLed(11);
}

void age3() {
  // Turn off attractions unsuitable for 25+ year olds
  Serial.println("Turning off place not for 25+ year olds");
  clearLed(11);
  clearLed(13);
}

void height() {
  // Turn off attractions with a 4ft requirement
  Serial.println("Turning off attractions with a 4ft requirement");
  clearLed(4);
  clearLed(8);
  clearLed(2);
  clearLed(5);
}

void time5() {
  // Turn off 5 minute attractions
  Serial.println("Turning off 5 minute attractions");
  clearLed(0);
  clearLed(1);
  clearLed(5);
  clearLed(7);
  clearLed(14);
}

void time10() {
  // Turn off 10 minute attractions
  Serial.println("Turning off 10 minute attractions");
  
  clearLed(2);
  clearLed(3);
  clearLed(4);
  clearLed(11);
  clearLed(12);
}

void time15() {
  // Turn off 15 minute attractions
  Serial.println("Turning off 15 minute attractions");
  clearLed(8);
  clearLed(9);
  clearLed(10);
  clearLed(13);
  clearLed(6);
}

void water() {
  // Turn off water rides
  Serial.println("Turning off water rides");
  clearLed(4);
  clearLed(2);
  clearLed(8);
}

void updateShiftRegisterOut(){
  Serial.print(ledStatesTop, BIN);
  Serial.println(ledStatesBottom, BIN);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatesBottom);
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatesTop);
  digitalWrite(latchPin, HIGH);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  switchResponses[0] = age1;
  switchResponses[1] = age2;
  switchResponses[2] = age3;
  switchResponses[3] = height;
  switchResponses[4] = time5;
  switchResponses[5] = time10;
  switchResponses[6] = time15;
  switchResponses[7] = water;
  
  Serial.begin(9600);

  Serial.println("Starting");
  delay(200);
}

void loop() {
  resetLeds();
  (switchResponses[loopIterator])();
//  Serial.println(switchResponses[loopIterator]);
  updateShiftRegisterOut();

  if (loopIterator == 15) {
    Serial.println("----------- starting over -----------");
  }
  
  loopIterator = (loopIterator + 1) % 16;
  
  delay(500);
  
}
