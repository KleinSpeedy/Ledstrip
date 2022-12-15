#pragma once
/* Global Includes */
#include <stdint.h>
#include <Arduino.h>

#define FASTLED_INTERNAL // turn off warnings
#include <FastLED.h>

/* Local Includes */


class EffectInterface
{
public:
    void setEncoding(uint8_t val)
    {
        encoding_ = val;
    };

    void setLedStrip(CRGB *ledStrip)
    {
        ledStrip_ = ledStrip;
    };

    virtual void draw() = 0;

protected:
    uint8_t encoding_;
    
    CRGB *ledStrip_;
    static constexpr int NUM_LEDS = 600;
};
