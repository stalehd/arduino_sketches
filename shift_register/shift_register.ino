//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(0));
  
}

bool bits[] = { 0, 0, 0, 0, 0, 0, 0 , 0, 0, 0, 0, 0, 0, 0, 0 };
#define BITS 15
int number = 1;
int d = 1;
void loop() {
  
  // count from 0 to 255 and display the number 
  // on the LEDs
  //number = random(256);
  for (int i = 0; i < BITS; i++) {
    bits[i] = 0;
  }
  bits[number] = 1;

  shiftBits();
  // pause before next value:
  delay(20);

  if (number >= (BITS - 1) || number <= 0) {
    d = -d;
  }
  number += d;
}

void shiftBits() {
  // Turn of latch pin to avoid flickering
  digitalWrite(latchPin, LOW);
  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);
  for (int i = 0; i < BITS; i++) {
    digitalWrite(clockPin, 0);
    digitalWrite(dataPin, bits[i] ? 1 : 0);
    digitalWrite(clockPin, 1);
    digitalWrite(dataPin, 0);
  }
  digitalWrite(clockPin, 0);
  // Set latch bin to switch to new state
  digitalWrite(latchPin, HIGH);
    
}

