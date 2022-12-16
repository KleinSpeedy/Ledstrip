/* Global Includes */

/* Local Includes */
#include "LightsEffect.h"

LightsEffect::LightsEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

void LightsEffect::draw()
{
    uint16_t position_ = beatsin16(8, 0, NUM_LEDS-1, 0, 0);
    uint8_t color = beatsin8(5, 0, 255, 0, 0);

    ledStrip_[position_] = CHSV(color, 255, 255);
    ledStrip_[NUM_LEDS - position_] = CHSV(255 - color, 255, 255);

    fadeToBlackBy(ledStrip_, NUM_LEDS, 25);
}