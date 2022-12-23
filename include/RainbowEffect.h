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
    std::array<CRGB,NUM_LEDS*10> stretchedStrip {};
    uint8_t index = 0;
};
