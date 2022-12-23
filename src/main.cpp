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
#include "HeatWaveEffect.h"
#include "RainbowEffect.h"

/* Globals */

constexpr int NUM_LEDS = 600;
static constexpr int LED_DATA_PIN = 0;

#define MSG_LEN 256

// Relais Pins

static constexpr uint8_t PIN_RELAIS_1 = 1;
static constexpr uint8_t PIN_RELAIS_2 = 2;
static constexpr uint8_t PIN_RELAIS_3 = 3;
static constexpr uint8_t PIN_RELAIS_4 = 4;

CRGB g_ledStrip[NUM_LEDS] {{}};
uint8_t g_ledBrightness = 255;

/* Encodings */

enum Encoding : uint8_t
{
  christmas = 0,
  fireworks,
  lights,
  snowflakes,
  balls,
  heatwave,
  rainbow
};

uint8_t g_encoding = Encoding::snowflakes;

/* Effect objects */

ChristmasEffect effect_christmas {Encoding::christmas, g_ledStrip};
FireworkEffect effect_fireworks {Encoding::fireworks, g_ledStrip};
LightsEffect effect_lights {Encoding::lights, g_ledStrip};
SnowFlakeEffect effect_snowflakes {Encoding::snowflakes, g_ledStrip};
BallEffect effect_balls {Encoding::balls, g_ledStrip, NUM_LEDS, 3, 0, true};
HeatWaveEffect effect_heatwave {Encoding::heatwave, g_ledStrip};
RainbowEffect effect_rainbow {Encoding::rainbow, g_ledStrip};

/* Functions */

void updateEncoding();

void setup()
{
  pinMode(PIN_RELAIS_1, INPUT_PULLUP);
  pinMode(PIN_RELAIS_2, INPUT_PULLUP);
  pinMode(PIN_RELAIS_3, INPUT_PULLUP);
  pinMode(PIN_RELAIS_4, INPUT_PULLUP);

  Serial.begin(9600);

  FastLED.addLeds<WS2812B, LED_DATA_PIN, GRB>(g_ledStrip, NUM_LEDS);

  FastLED.setBrightness(g_ledBrightness);
  FastLED.setMaxPowerInMilliWatts(50000);

  FastLED.clear(true);
}

uint8_t buffer[MSG_LEN] = {{}};

void loop()
{
  // TODO: make this a ISR
  //updateEncoding();

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
    case Encoding::heatwave:
    {
      effect_heatwave.draw();
      break;
    }
    case Encoding::rainbow:
    {
      effect_rainbow.draw();
      break;
    }
    default:
      break;
  }

  FastLED.show();
}

void updateEncoding()
{
  uint8_t value1 = 0, value2 = 0, value3 = 0, value4 = 0;

  value1 = digitalRead(PIN_RELAIS_1);
  value2 = digitalRead(PIN_RELAIS_2);
  value3 = digitalRead(PIN_RELAIS_3);
  value4 = digitalRead(PIN_RELAIS_4);

  g_encoding = (value1) | (value2 << 1) | (value3 << 2) | (value4 << 3);
}