#include <FastLED.h>


// The LuMini matrices need two data pins connected, these two pins are common on many microcontrollers, but can be changed according to your setup
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds

// Params for width and height
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 8;

#define NUM_LEDS kMatrixWidth * kMatrixHeight;

const bool    kMatrixSerpentineLayout = false;
// Set 'kMatrixSerpentineLayout' to false as the pixels in the LuMini matrices are laid out
//
//     0 >  1 >  2 >  3 >  4
//                         |
//     .----<----<----<----'
//     |
//     5 >  6 >  7 >  8 >  9
//                         |
//     .----<----<----<----'
//     |
//    10 > 11 > 12 > 13 > 14
//                         |
//     .----<----<----<----'
//     |
//    15 > 16 > 17 > 18 > 19
//

CRGB matrix[NUM_LEDS];

void setup() {
  Serial.begin(57600);
  Serial.println("resetting");
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(matrix, NUM_LEDS);
  LEDS.setBrightness(32);
}

void fadeAll() {
  for (int i = 0; i < NUM_LEDS; i++)
  {
    matrix[i].nscale8(250);
  }
}

void loop()
{
  for (int i = 0; i < 3; i++)
  {
    uint8_t angle = round(i * 85.3333) + rotation;
    ring[ringMap[angle]] = CHSV(angle, 127, 255);
  }
  FastLED.show();
  rotation++;
  fadeAll(248);
  delay(5);
}
