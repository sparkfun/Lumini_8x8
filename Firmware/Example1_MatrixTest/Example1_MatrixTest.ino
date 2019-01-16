#include <FastLED.h>

// How many leds in your chain? Change the value of NUM_BOARDS depending on your setup
#define NUM_BOARDS 1
#define NUM_LEDS 64 * NUM_BOARDS //64 LED's per board

// The LuMini matrices need two data pins connected, these two pins are common on many microcontrollers, but can be changed according to your setup
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds
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

void loop() {
  static uint8_t hue = 0;
  //Rotate around the circle
  for (int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to the current hue
    matrix[i] = CHSV(hue++, 150, 255); //display the current hue, then increment it.
    // Show the leds
    FastLED.show();
    fadeAll();//Reduce the brightness of all LEDs so our LED's fade off with every frame.
    // Wait a little bit before we loop around and do it again
    delay(5);
  }
}
