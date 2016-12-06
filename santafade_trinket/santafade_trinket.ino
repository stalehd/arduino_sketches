int green_led = 0;
int red_led = 1;
int brightness = 0;
int fade = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
}

void loop() {
  analogWrite(red_led, brightness);
  analogWrite(green_led, 255 - brightness);
  brightness = brightness + fade;
  if (brightness <= 0 || brightness >= 255) {
    fade = -fade;
  }
  delay(30);
}
