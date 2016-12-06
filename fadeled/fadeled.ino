int rPin = 3;
int gPin = 5;
int yPin = 6;
void setup() {
  // put your setup code here, to run once:
}

void loop() {
  int gFade = 100;
  int gDirection = 5;
  int yFade = 50;
  int yDirection = 5;
  int rFade = 0;
  int rDirection = 5;
  
  while (1) {
    analogWrite(rPin, rFade);
    analogWrite(yPin, yFade);
    analogWrite(gPin, gFade);
    rFade += rDirection;
    yFade += yDirection;
    gFade += gDirection;
    if (rFade >= 255 || rFade < 5) {
      rDirection = -rDirection;
    }
    if (yFade >= 255 || yFade < 5) {
      yDirection = -yDirection;
    }
    if (gFade >= 255 || gFade < 5) {
      gDirection = -gDirection;
    }
    delay(50);  
  }
}
