#pragma once
/* Global Includes */
#include <array>
#include <cmath>

/* Local Includes */
#include "EffectInterface.h"

class RainbowEffect : public EffectInterface
{
public:
    RainbowEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    const uint8_t hueDensity_ = 4;  // 
    const uint8_t deltaHue_ = 1;    // drawingSpeed low - stretched out, high - tightly packed

    uint8_t initialHue_ = 0;
};
