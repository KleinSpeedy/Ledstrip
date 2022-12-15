/* Global Includes */
#include <Arduino.h>
#define FASTLED_INTERNAL // turn off warnings
#include <FastLED.h>

/* Local Includes */
#include "ChristmasEffect.h"
#include "FireworkEffect.h"
#include "LightsEffect.h"
#include "SnowFlakeEffect.h"
#include "BallEffect.h"

constexpr int NUM_LEDS = 600;
constexpr int LED_DATA_PIN = 0;

CRGB g_ledStrip[NUM_LEDS] {{0}};
uint8_t g_ledBrightness = 255;

ChristmasEffect christmas {1, g_ledStrip};
FireworkEffect fireworks {2, g_ledStrip};
LightsEffect lights {3, g_ledStrip};
SnowFlakeEffect snowflakes {4, g_ledStrip};
BallEffect balls {5, g_ledStrip, NUM_LEDS, 1, 1, false};

void setup()
{
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(g_ledStrip, NUM_LEDS);

  FastLED.setBrightness(g_ledBrightness);
  FastLED.setMaxPowerInMilliWatts(50000);

  FastLED.clear(true);
}

void loop()
{
  balls.draw();
  FastLED.show();
}