/* Global Includes */

/* Local Includes */
#include "ChristmasEffect.h"

ChristmasEffect::ChristmasEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

void ChristmasEffect::draw()
{
    Serial.print("Enc: ");
    Serial.print(encoding_);
    Serial.print(" NumLeds: ");
    Serial.println(NUM_LEDS);
}