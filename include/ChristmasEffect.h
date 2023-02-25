#pragma once
/* Global Includes */

/* Local Includes */
#include "EffectInterface.h"

class ChristmasEffect : public EffectInterface
{
public:
    ChristmasEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    CRGB colorFraction(CRGB inColor, float fraction);
    void drawPixels(float fPos, float count, CRGB color);
};
