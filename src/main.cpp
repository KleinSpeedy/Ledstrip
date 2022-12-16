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

/* Encodings */
enum Encoding : uint8_t
{
  christmas = 0,
  fireworks,
  lights,
  snowflakes,
  balls
};

uint8_t g_encoding = Encoding::lights;

CRGB g_ledStrip[NUM_LEDS] {{0}};
uint8_t g_ledBrightness = 255;

ChristmasEffect effect_christmas {Encoding::christmas, g_ledStrip};
FireworkEffect effect_fireworks {Encoding::fireworks, g_ledStrip};
LightsEffect effect_lights {Encoding::lights, g_ledStrip};
SnowFlakeEffect effect_snowflakes {Encoding::snowflakes, g_ledStrip};
BallEffect effect_balls {Encoding::balls, g_ledStrip, NUM_LEDS, 3, 0, true};

void setup()
{
  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(g_ledStrip, NUM_LEDS);

  FastLED.setBrightness(g_ledBrightness);
  FastLED.setMaxPowerInMilliWatts(50000);

  FastLED.clear(true);
}

void loop()
{

  switch(g_encoding)
  {
    case Encoding::christmas:
    {
      effect_christmas.draw();
      break;
    }
    case Encoding::fireworks:
    {
      effect_fireworks.draw();
      break;
    }
    case Encoding::lights:
    {
      effect_lights.draw();
      break;
    }
    case Encoding::snowflakes:
    {
      effect_snowflakes.draw();
      break;
    }
    case Encoding::balls:
    {
      effect_balls.draw();
      break;
    }
    default:
      break;
  }

  FastLED.show();
}