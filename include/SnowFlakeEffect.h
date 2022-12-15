#pragma once
/* Global Includes */
#include <array>

/* Local Includes */
#include "EffectInterface.h"


class SnowFlakeEffect : public EffectInterface
{
public:
    SnowFlakeEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    CRGBPalette16 snowPalette;
};
