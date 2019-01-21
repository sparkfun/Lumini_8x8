#include <FastLED.h>

//How many matrices are you using?
#define NUM_MATRICES 1
#define NUM_LEDS 64 * NUM_MATRICES

//Data and Clock Pins
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds
CRGB matrix[NUM_LEDS];

uint8_t matrixWidth = 8;
uint8_t matrixHeight = 8;

//Gradient Variables

uint8_t rotation = 0;
uint8_t brightness = 255;

TBlendType    currentBlending = LINEARBLEND;
CRGBPalette16 currentPalette = {
  CHSV(5, 190, 255),
  CHSV(0, 190, 255),
  CHSV(245, 255, 255),
  CHSV(235, 235, 255),
  CHSV(225, 235, 255),
  CHSV(225, 150, 255),
  CHSV(16, 150, 255),
  CHSV(16, 200, 255),
  CHSV(16, 225, 255),
  CHSV(0, 255, 255),
  CHSV(72, 200, 255),
  CHSV(115, 225, 255),
  CHSV(40, 255, 255),
  CHSV(35, 255, 255),
  CHSV(10, 235, 255),
  CHSV(5, 235, 255)
};

//Uncomment any of these palettes to change to the built in FastLED Palettes
//currentPalette = RainbowColors_p;
//currentPalette =  RainbowStripeColors_p;
//currentPalette = OceanColors_p;
//currentPalette = CloudColors_p;
//currentPalette = LavaColors_p;
//currentPalette = ForestColors_;
//currentPalette = PartyColors_p;

//We'll use a simple XY mapping for a single matrix
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  i = (y * matrixWidth) + x;
  return i;
}

void setup()
{
  Serial.begin(115200);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(matrix, NUM_LEDS);
  FastLED.setBrightness(32);
}

void loop() {
  for (uint8_t x = 0; x < matrixWidth; x++)
  {
    uint8_t gradientIndex = (x * 2) + rotation;//Multiply by 2 to show more of the gradient on the matrix
    for (uint8_t y = 0; y < matrixHeight; y++)
    {
      matrix[XY(x, y)] = ColorFromPalette(currentPalette, gradientIndex, brightness, currentBlending);
    }
  }
  FastLED.show();
  rotation++;
  delay(30);
}
