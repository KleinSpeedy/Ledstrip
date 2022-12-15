/* Global Includes */

/* Local Includes */
#include "LightsEffect.h"

LightsEffect::LightsEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

int randomNumber;
void LightsEffect::draw()
{
    fadeToBlackBy(ledStrip_, NUM_LEDS, 1);

    EVERY_N_MILLISECONDS(50)
    {
        randomNumber = random8(5);
        ledStrip_[random16(0,NUM_LEDS-1)] = colors.at(randomNumber);
    }
}