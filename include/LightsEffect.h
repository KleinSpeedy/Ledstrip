#pragma once
/* Global Includes */
#include <array>

/* Local Includes */
#include "EffectInterface.h"

class LightsEffect : public EffectInterface
{
public:
    LightsEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    const std::array<CRGB, 5> colors = {
        CRGB::Magenta,
        CRGB::BlueViolet,
        CRGB::Amethyst,
        CRGB::Orange,
        CRGB::Aquamarine
    };
};
