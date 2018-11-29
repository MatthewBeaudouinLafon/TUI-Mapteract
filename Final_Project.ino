int led1 = 2;
int led2 = 3;
int led3 = 4;

int tab1 = 13;
int tab2 = 12;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(tab1, INPUT);
  pinMode(tab2, INPUT);

  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  Serial.begin(9600);
}

void loop() {
  int tab1_val = digitalRead(tab1);
  int tab2_val = digitalRead(tab2);
  
  Serial.print("Tab1 Value: ");
  Serial.println(tab1_val);
  Serial.print("Tab2 Value: ");
  Serial.println(tab2_val);
  Serial.println();

  int led1_val = HIGH;
  int led2_val = HIGH;
  int led3_val = HIGH;

  
  // if the the first tab closes the circuit, then leds 2 and 3 turn off
  if (tab1_val == 1){
    led2_val = LOW;
    led3_val = LOW;
  }
    
  // if the the second tab closes the circuit, then leds 1 and 2 turn off
  if (tab2_val == 1){
    led1_val = LOW;
    led2_val = LOW;
  }

  digitalWrite(led1, led1_val);
  digitalWrite(led2, led2_val);
  digitalWrite(led3, led3_val);

  
  delay(100);

}
