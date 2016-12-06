#include <Adafruit_NeoPixel.h>

// Pixel slider (c) 2016 Ståle Dahl <stalehd@gmail.com>
// NeoPixel colour slider strip. Three pixels with primary colours are moving in the same 
// direction with different speeds. Uses a Neopixel strip from Adafruit connected to pin 6. 
// 

// Data pin for NeoPixels
#define PIN 6
// Number of pixels.
#define NUMPIXELS 20
// Delay between movements. Lower => faster. 
#define BASEDELAY 100
// The max brightness
#define MAXBRIGHT 128
// Number of pixels to fade. Brightness is halved for each iteration
#define FADE_STEPS 6


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Internal counter. Just for keeping track of time.
int counter = 0;
// Position of each pixel.
int positions[] = { 0, 0, 0 };

// Cache of RGB values for each pixel. The pixel library probably keeps this 
// in memory somewhere as well but better to keep our hands out of that.
typedef struct {
  byte r;
  byte g;
  byte b;
} t_rgb;

// The array itself. 
t_rgb *rgb_pos;

void setup() {
  pixels.begin();
  rgb_pos = malloc(sizeof(t_rgb) * NUMPIXELS);
}

void loop() {

  // Blank all pixels that are set
  for (int i = 0; i < NUMPIXELS; i++) {
    if (rgb_pos[i].r > 0 || rgb_pos[i].g > 0 || rgb_pos[i].b > 0) {
      pixels.setPixelColor(i, 0);
      rgb_pos[i].r = 0;
      rgb_pos[i].g = 0;
      rgb_pos[i].b = 0;
    }
  }

  // Move the three pixels. Note that 0 and 1 falls through so the 
  // multiplication is implicit
  switch (counter) {
    case 0: // Red pixel movement (the slowest)
      positions[0] = (positions[0] + 1) % NUMPIXELS;
    case 1: // Green pixel movement 
      positions[1] = (positions[1] + 1) % NUMPIXELS;
    case 2: // Blue pixel movement (the fastestst)
      positions[2] = (positions[2] + 1) % NUMPIXELS;
  }

  // Set main pixels in cache
  int bright = MAXBRIGHT;
  rgb_pos[positions[0]].r = bright;
  rgb_pos[positions[1]].g = bright;
  rgb_pos[positions[2]].b = bright;
  bright /= 2;
  // Set trail of fading pixels
  for (int i = 0; i < FADE_STEPS; i++) {
    rgb_pos[(positions[0] - i + NUMPIXELS) % NUMPIXELS].r = bright;
    rgb_pos[(positions[1] - i + NUMPIXELS) % NUMPIXELS].g = bright;
    rgb_pos[(positions[2] - i + NUMPIXELS) % NUMPIXELS].b = bright;
    bright /= 2;
  }


  // Finally, set the pixels. Just set the ones with values.
  for (int i = 0; i < NUMPIXELS; i++) {
    if (rgb_pos[i].r > 0 || rgb_pos[i].g > 0 || rgb_pos[i].b > 0) {
      pixels.setPixelColor(i, pixels.Color(rgb_pos[i].r, rgb_pos[i].g, rgb_pos[i].b));
    }
  }
  pixels.show();
  
  counter = (counter + 1) % 3;

  delay(BASEDELAY);
}
