#include <FastLED.h>

//How many matrices are you using?
#define NUM_MATRICES 4
#define NUM_LEDS 64 * NUM_MATRICES

// The LuMini matrices need two data pins connected
#define DATA_PIN 16
#define CLOCK_PIN 17

// Define the array of leds
CRGB matrix[NUM_LEDS];

//The Height and Width of each individual matrix
int individualMatrixWidth = 8;
int individualMatrixHeight = 8;

const int moduleHeight = 2; //The Height of our display, measured in numbers of LuMini matrices
const int moduleWidth = 2; //The Width of our display, measured in numbers of LuMini matrices

//The following matrix represents our entire LED display, with the number that each module is in the chain. My data flows in to the bottom left matrix (matrix 0 in my chain),
//then it goes right to the bottom right matrix (matrix 1 in my chain) then up to the top right matrix (matrix 2) then to the remaining matrix 3
//The below table should have identical matrix numbers/positions as that of the multi-matrix display
int matrixMap[moduleHeight][moduleWidth] = {
  {3, 2},
  {0, 1}
};


//Not every matrix will have the same orientation (matrices may be rotated 90, 180, or 270 degrees from each other)
//Properly oriented matrices will show a line of color wiping from left to right if their orientation is 0
//If a matrix shows any of the following color wipes, change it's orientation to the corresponding number:
//Top to Bottom: 1
//Right to Left: 2
//Bottom to Top: 3
int orientation[moduleHeight * moduleWidth] = { 0, 0, 0, 1 };

void fadeAll(uint8_t scale = 250)
{
  for (int i = 0; i < NUM_LEDS; i++)
  {
    matrix[i].nscale8(scale);
  }
}

uint16_t XY( uint16_t x, uint16_t y)
{
  uint16_t i;
  uint8_t matrixNum = matrixMap[(moduleHeight - 1) - (y / individualMatrixHeight)][x / individualMatrixWidth]; //Calculates which matrix we are on using the matrix map
  uint8_t relativeX; //x position relative to the origin of the current matrix
  uint8_t relativeY; //y position relative to the origin of the current matrix
  switch (orientation[matrixNum])//Transposes our values based on orientation
  {
    case 0:
      relativeX = x % individualMatrixWidth;
      relativeY = y % individualMatrixHeight;
      break;
    case 1:
      relativeX = 7 - (y % individualMatrixWidth);
      relativeY = x % individualMatrixHeight;
      break;
    case 2:
      relativeX = 7 - (x % individualMatrixWidth);
      relativeY = y % individualMatrixHeight;
      break;
    case 3:
      relativeX = y % individualMatrixWidth;
      relativeY = x % individualMatrixHeight;
      break;
  }
  i = (relativeY * individualMatrixWidth) + relativeX; //Calculates where we are on a matrix
  i += matrixNum * individualMatrixWidth * individualMatrixHeight; //Adds on offset based on which matrix we're on in the chain.
  return i;
}

void setup() {
  Serial.begin(115200);
  LEDS.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(1)>(matrix, NUM_LEDS);
  LEDS.setBrightness(32);
}

void loop() {
  static uint8_t hue = 0;
  //Draw vertical bars from left to right
  for (int x = 0; x < 16; x++)
  {
    for (int y = 0; y < 16; y++)
    {
      // Set the i'th led to the current hue
      matrix[XY(x, y)] = CHSV(hue, 150, 255); //display the current hue, then increment it.
    }
    FastLED.show();
    delay(20);
    fadeAll(127);//Reduce the brightness of all LEDs so our LED's fade off with every frame.
    hue++;
  }
}

