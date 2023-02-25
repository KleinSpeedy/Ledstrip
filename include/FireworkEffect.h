#pragma once
/* Global Includes */

/* Local Includes */
#include "EffectInterface.h"

class FireworkEffect : public EffectInterface
{
public:
    FireworkEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    CRGBPalette16 gPal1_ = CRGBPalette16(CRGB::Black, CRGB::Orange, CRGB::Red, CRGB::White);
    CRGBPalette16 gPal2_ = CRGBPalette16(CRGB::Black, CRGB::DarkBlue, CRGB::Aqua, CRGB::White);
    CRGBPalette16 gPal3_ = CRGBPalette16(CRGB::Black, CRGB::DarkGreen, CRGB::Yellow, CRGB::White);

    const static int NUM_SPARKS = 40; // max number (could be NUM_LEDS / 2);
    const int maxPos = (NUM_LEDS - 1) * 128;
    int sparkPos[3][NUM_SPARKS];
    int sparkVel[3][NUM_SPARKS];
    int sparkHeat[3][NUM_SPARKS];
    int flarePos[3];
    bool flareShot[3] = {false, false, false};
    byte nSparks[3];

    void shoot(byte nr);
    void doSparks(byte nr);
};
