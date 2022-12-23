#pragma once
/* Global Includes */

/* Local Includes */
#include "EffectInterface.h"

class HeatWaveEffect : public EffectInterface
{
public:
    HeatWaveEffect(uint8_t encoding, CRGB *ledStrip);

    void draw() override;

private:
    uint8_t index_ = 0;
};
