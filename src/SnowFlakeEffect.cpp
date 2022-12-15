/* Global Includes */

/* Local Includes */
#include "SnowFlakeEffect.h"

// Gradient palette "frost_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nord/tn/frost.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 32 bytes of program space.
DEFINE_GRADIENT_PALETTE( frost_gp )
{
    0,   56, 130, 117,
    63,  56, 130, 117,
    63,  49, 136, 153,
    127, 49, 136, 153,
    127, 43,  92, 127,
    191, 43,  92, 127,
    191, 19,  56,  95,
    255, 19,  56,  95
};

SnowFlakeEffect::SnowFlakeEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
    snowPalette = frost_gp;
};

void SnowFlakeEffect::draw()
{
    fadeToBlackBy(ledStrip_, NUM_LEDS, 1);
    delay(5);

    EVERY_N_MILLISECONDS(35)
    {
        ledStrip_[random16(0,NUM_LEDS-1)] = ColorFromPalette(snowPalette, random8(), 255);
    }
}