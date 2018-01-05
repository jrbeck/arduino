// testcolors demo for Adafruit RGBmatrixPanel library.
// Renders 512 colors on our 16x32 RGB LED matrix:
// http://www.adafruit.com/products/420
// Library supports 4096 colors, but there aren't that many pixels!  :)
// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define CLK 8  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2

RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

void setup() {
  matrix.begin();
  uint8_t r=0, g=0, b=0;
  // Draw top half
  for (uint8_t x=0; x < 32; x++) {
    for (uint8_t y=0; y < 8; y++) {
      matrix.drawPixel(x, y, matrix.Color333(r, g, b));
      r++;
      if (r == 8) {
        r = 0;
        g++;
        if (g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }
  // Draw bottom half
  for (uint8_t x=0; x < 32; x++) {
    for (uint8_t y=8; y < 16; y++) {
      matrix.drawPixel(x, y, matrix.Color333(r, g, b));
      r++;
      if (r == 8) {
        r = 0;
        g++;
        if (g == 8) {
          g = 0;
          b++;
        }
      }
    }
  }
}

#define SCREEN_W 32
#define SCREEN_H 16

int gX = 0;
int gY = 0;
int gVX = 1;
int gVY = 1;

void loop() {
  // do nothing
  matrix.drawPixel(gX, gY, matrix.Color333(0, 0, 0));

  gX += gVX;
  if (gX == 0) {
    gVX = 1;
  }
  if (gX == SCREEN_W - 1) {
    gVX = -1;
  }

  gY += gVY;
  if (gY == 0) {
    gVY = 1;
  }
  if (gY == SCREEN_W - 1) {
    gVY = -1;
  }

  matrix.drawPixel(gX, gY, matrix.Color333(16, 16, 16));
}
