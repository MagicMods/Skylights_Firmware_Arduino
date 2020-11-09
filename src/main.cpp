#include <Arduino.h>
#include "Palettes.h"
#include <FastLED.h> // // // // // // // // // // // // // // // // // // // // // //
#include "main.h"
#include "WifUdp.h" 

FASTLED_USING_NAMESPACE

#define DATA_PIN_CEILLING D5
#define DATA_PIN_DESK D6
#define DATA_PIN_BED D3
#define DATA_PIN_WINR D7
#define DATA_PIN_WINL D8
//#define CLK_PIN   4
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define NUM_LEDS_CEILLING 493
#define NUM_LEDS_DESK 99
#define NUM_LEDS_BED 96
#define NUM_LEDS_WIN 66

CRGB leds_ceilling[NUM_LEDS_CEILLING];
CRGB leds_desk[NUM_LEDS_DESK];
CRGB leds_bed[NUM_LEDS_BED];
CRGB leds_winr[NUM_LEDS_WIN];
CRGB leds_winl[NUM_LEDS_WIN];

// #define BRIGHTNESS 80
#define FRAMES_PER_SECOND 120
uint8_t BRIGHTNESS = 80;

bool onOff[4] = {1, 1, 1, 1};

CRGBPalette16 currentPalette;
TBlendType currentBlending;

bool bed = true;
bool autoColor = true;
String sColor = "rainbow";

void setup()
{
  Serial.begin(115200);
  delay(1000); // 3 second delay for recovery
  SetupWifi();
  // tell FastLED about the LED strip configuration
  FastLED.addLeds<LED_TYPE, DATA_PIN_CEILLING, COLOR_ORDER>(leds_ceilling, NUM_LEDS_CEILLING).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_DESK, COLOR_ORDER>(leds_desk, NUM_LEDS_DESK).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_BED, COLOR_ORDER>(leds_bed, NUM_LEDS_BED).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_WINR, COLOR_ORDER>(leds_winr, NUM_LEDS_WIN).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<LED_TYPE, DATA_PIN_WINL, COLOR_ORDER>(leds_winl, NUM_LEDS_WIN).setCorrection(TypicalLEDStrip);
  //FastLED.addLeds<LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER>(leds, NUM_LEDS_CEILLING).setCorrection(TypicalLEDStrip);

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  currentBlending = LINEARBLEND;
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {
    rainbow,
    // fire,
    // breath,
    // sinelon2,
    // rainbowWithGlitter,
    // confetti,
    // sinelon,
    // juggle,
    // bpm
};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0;                  // rotating "base color" used by many of the patterns

void loop()
{
  EVERY_N_MILLISECONDS(200) { gHue++; }

  UdpRead();
  uint8_t value = incomingPacket[1];
  Serial.print(incomingPacket);
  switch (incomingPacket[0])
  {

  case 3:
  {
    // Serial.print("Brightness :");
    BRIGHTNESS = value;
    FastLED.setBrightness(BRIGHTNESS);
    // Serial.println(BRIGHTNESS);
    }
    break;
    case 4:
    {
      Serial.print("Saturation");
      Serial.println(value);
    }
    break;
    case 5:
    {
      Serial.print("Color");
      Serial.println(value);
    }
    break;
    case 6:
    {
      Serial.print("Patterns");
      Serial.println(value);
    }
    case 10:
    {
      Serial.print("Bed ");
      Serial.println(incomingPacket[1]);
      if (incomingPacket[1] == 0)
      {
        onOff[0] = false;
      }
      else if (incomingPacket[1] == 1)
      {
        onOff[0] = true;
      }
      break;
    }
    case 11:
    {
      Serial.print("Desk ");
      Serial.println(incomingPacket[1]);
      if (incomingPacket[1] == 0)
      {
        onOff[1] = false;
      }
      else if (incomingPacket[1] == 1)
      {
        onOff[1] = true;
      }
      break;
    }
    case 12:
    {
      Serial.print("Ceilling ");
      Serial.println(incomingPacket[1]);
      if (incomingPacket[1] == 0)
      {
        onOff[2] = false;
      }
      else if (incomingPacket[1] == 1)
      {
        onOff[2] = true;
      }
      break;
    }
    case 13:
    {
      Serial.print("Window ");
      Serial.println(incomingPacket[1]);
      if (incomingPacket[1] == 0)
      {
        onOff[3] = false;
      }
      else if (incomingPacket[1] == 1)
      {
        onOff[3] = true;
      }
      break;
    }
    break;
    case 15:
    {
      sColor = String((char *)incomingPacket);
      sColor.remove(0, 1);
      Serial.println(sColor);

    }
    break;
    default:
      break;
    }
    
    if (packetSize != 0)
    {
      for(int i=0 ; i < packetSize; i++){
        incomingPacket[i] = 0;
      } 
    }
    // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();
    // ChangePalettePeriodically();
    // static uint8_t startIndex = 0;
    // startIndex = startIndex + 1; /* motion speed */
    // FillLEDsFromPaletteColors(startIndex);

    if (sColor == "rainbow"){
      rainbow();
    } else {

      if (sColor == "bhw1_01") { currentPalette = bhw1_01_gp; } 
      else if (sColor == "bhw1_04"){ currentPalette = bhw1_04_gp; }
      else if (sColor == "bhw1_purplered"){ currentPalette = bhw1_purplered_gp; }
      else if (sColor == "bhw1_w00t"){ currentPalette = bhw1_w00t_gp; }
      else if (sColor == "bhw2_51"){ currentPalette = bhw2_51_gp; }
      else if (sColor == "bhw2_57"){ currentPalette = bhw2_57_gp; }
      else if (sColor == "bhw2_n"){ currentPalette = bhw2_n_gp; }
      else if (sColor == "bhw3_23"){ currentPalette = bhw3_23_gp; }
      else if (sColor == "bhw3_52"){ currentPalette = bhw3_52_gp; }
      else if (sColor == "bhw4_018"){ currentPalette = bhw4_018_gp; }
      else if (sColor == "bhw4_024"){ currentPalette = bhw4_024_gp; }
      else if (sColor == "bhw4_048"){ currentPalette = bhw4_048_gp; }
      else if (sColor == "bhw4_057"){ currentPalette = bhw4_057_gp; }
      


      // currentPalette = sColor;
      static uint8_t startIndex = 0;
      startIndex = startIndex + 1; /* motion speed */
      FillLEDsFromPaletteColors(startIndex);
    }

    SwitchOnOff();
    
    FastLED.show();

    FastLED.delay(1000 / FRAMES_PER_SECOND);


}

void Color(){

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);
}

void FillLEDsFromPaletteColors(uint8_t colorIndex)
{
    if (onOff[0])
  {
  for (int i = 0; i < NUM_LEDS_BED; i++)
  {
    leds_bed[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
  }
      if (onOff[1])
  {
   
  for (int i = 0; i < NUM_LEDS_DESK; i++)
  {
    leds_desk[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
  }
    if (onOff[2])
  {
  for (int i = 0; i < NUM_LEDS_CEILLING; i++)
  {
    leds_ceilling[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
  }


      if (onOff[3])
  {
    for (int i = 0; i < NUM_LEDS_WIN; i++)
  {
    leds_winr[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
      for (int i = 0; i < NUM_LEDS_WIN; i++)
  {
    leds_winl[i] = ColorFromPalette(currentPalette, colorIndex, BRIGHTNESS, currentBlending);
    colorIndex += 1;
  }
  }
}



void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;

  if (lastSecond != secondHand)
  {
    lastSecond = secondHand;
    if (secondHand == 0)
    {
      currentPalette = RainbowColors_p;
    }
    if (secondHand == 5)
    {
      currentPalette = RainbowStripeColors_p;
    }
    if (secondHand == 10)
    {
      SetupTotallyRandomPalette();
    }
    if (secondHand == 15)
    {
      currentPalette = CloudColors_p;
    }
    if (secondHand == 20)
    {
      currentPalette = PartyColors_p;
    }
    if (secondHand == 25)
    {
      currentPalette = purplefly_gp;
    }
    if (secondHand == 30)
    {
      currentPalette = bhw1_sunconure_gp;
    }
    if (secondHand == 35)
    {
      currentPalette = bhw2_turq_gp;
    }
  }
}

void SetupTotallyRandomPalette()
{
  for (int i = 0; i < 16; i++)
  {
    currentPalette[i] = CHSV(random8(), 255, random8());
  }
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  if (onOff[0])
  {
    fill_rainbow(leds_bed, NUM_LEDS_BED, gHue, 1);
  }
  if (onOff[1])
  {
    fill_rainbow(leds_desk, NUM_LEDS_DESK, gHue, 1);
  }
  if (onOff[2])
  {
    fill_rainbow(leds_ceilling, NUM_LEDS_CEILLING, gHue, 1);
  }
    if (onOff[3])
  {
    fill_rainbow(leds_winr, NUM_LEDS_WIN, gHue, 1);
    fill_rainbow(leds_winl, NUM_LEDS_WIN, gHue, 1);
  }
}

void SwitchOnOff(){
    if (!onOff[0])
  {
    fadeToBlackBy(leds_bed, NUM_LEDS_BED, 1);
  }
  if (!onOff[1])
  {
    fadeToBlackBy(leds_desk, NUM_LEDS_DESK, 1);
  }
  if (!onOff[2])
  {
    fadeToBlackBy(leds_ceilling, NUM_LEDS_CEILLING, 1);
  }
    if (!onOff[3])
  {
    fadeToBlackBy(leds_winr, NUM_LEDS_WIN, 1);
    fadeToBlackBy(leds_winl, NUM_LEDS_WIN, 1);
  }
}

void rainbowtest()
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds_ceilling, NUM_LEDS_CEILLING, gHue, 1);
  fill_rainbow(leds_desk, NUM_LEDS_DESK, gHue, 1);
  fill_rainbow(leds_bed, NUM_LEDS_BED, gHue, 1);
}

void rainbowWithGlitter()
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter(int chanceOfGlitter)
{
  if (random8() < (fract8)chanceOfGlitter)
  {
    leds_ceilling[random16(NUM_LEDS_CEILLING)] += CRGB::White;
  }
}

void confetti()
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy(leds_ceilling, NUM_LEDS_CEILLING, 10);
  int pos = random16(NUM_LEDS_CEILLING);
  leds_ceilling[pos] += CHSV(gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy(leds_ceilling, NUM_LEDS_CEILLING, 2);
  int pos = beatsin16(13, 0, NUM_LEDS_CEILLING - 1);
  leds_ceilling[pos] += CHSV(gHue, 255, 192);
}

int bpmsinelonlast;
int bpmsinelon = 50;

void sinelon2()
{
  // a colored dot sweeping back and forth, with fading trails
  // int bpmsinelonup = map(wattsDrive, 0, 300, 0, 200);
  int bpmsinelonup = 100;

  int x = bpmsinelonup - bpmsinelonlast;

  if (x > 4 || x < -4)
  {
    bpmsinelon = bpmsinelonup;
    Serial.println(bpmsinelon);
    Serial.println(x);
  }
  else
  {
    bpmsinelon = bpmsinelonlast;
  }

  fadeToBlackBy(leds_ceilling, NUM_LEDS_CEILLING, 4);
  int pos = beatsin16(bpmsinelon, 0, NUM_LEDS_CEILLING);
  // int tempDrive = map(temps[0], 20, 71, 192, 70);
  int tempDrive = 140;
  Serial.println(tempDrive);
  leds_ceilling[pos] += CHSV(gHue, 255, 200);
  bpmsinelonlast = bpmsinelon;
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 6;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
  for (int i = 0; i < NUM_LEDS_CEILLING; i++)
  { //9948
    leds_ceilling[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void juggle()
{
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy(leds_ceilling, NUM_LEDS_CEILLING, 20);
  byte dothue = 0;
  for (int i = 0; i < 80; i++)
  {
    leds_ceilling[beatsin16(i + 7, 0, NUM_LEDS_CEILLING - 1)] |= CHSV(dothue, 200, 255);
    for (int i = 0; i < 80; i++)
    {
      leds_ceilling[beatsin16(i + 7, 0, NUM_LEDS_CEILLING - 1)] |= CHSV(dothue, 200, 255);
      dothue += 32;
    }
  }
}

bool gReverseDirection;

void fire()
{
  // Array of temperature readings at each simulation cell
  static byte heat[NUM_LEDS_CEILLING];
  // int cooling = map(wattsDrive, 0, 300, 150, 20);
  int cooling = 80;
  int coolinglast;
  if (cooling != coolinglast)
  {
    Serial.println("cooling");
    Serial.print(cooling);
  }
  coolinglast = cooling;
  // Step 1.  Cool down every cell a little
  for (int i = 0; i < NUM_LEDS_CEILLING; i++)
  {
    heat[i] = qsub8(heat[i], random8(0, ((cooling * 10) / NUM_LEDS_CEILLING) + 2));
  }

  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for (int k = NUM_LEDS_CEILLING - 1; k >= 2; k--)
  {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
  // int sparkling = map(wattsDrive, 0, 300, 0, 100);
  int sparkling = 50;
  Serial.println("sparkling");
  Serial.print(sparkling);
  // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
  if (random8() < sparkling)
  {
    int y = random8(7);
    heat[y] = qadd8(heat[y], random8(10, 255));
  }

  // Step 4.  Map from heat cells to LED colors
  for (int j = 0; j < NUM_LEDS_CEILLING; j++)
  {
    CRGB color = HeatColor(heat[j]);
    int pixelnumber;
    if (gReverseDirection)
    {
      pixelnumber = (NUM_LEDS_CEILLING - 1) - j;
    }
    else
    {
      pixelnumber = j;
    }
    leds_ceilling[pixelnumber] = color;
  }
}

int bpmBreathchange;
int bpmBreathlast;

void breath()
{
  int bpmBreath = 40;
  // Serial.println(y);

  unsigned int y = bpmBreathchange - bpmBreathlast;

  if (y > 5)
  {
    bpmBreath = bpmBreathchange;
    Serial.println(y);
  }
  else
  {
    bpmBreath = bpmBreathchange;
    Serial.println(y);
  }

  int redLevel = beatsin16(bpmBreath, 0, 255);                          //generate a sine wave with a freq of bpmRed from a low of 0 and a high of 255
  fill_solid(leds_ceilling, NUM_LEDS_CEILLING, CRGB(redLevel, 0, 128)); //fill the RGB pixel array with: redLevel, 0, 0
  bpmBreathlast = bpmBreath;
}
