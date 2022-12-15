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
    uint8_t encoding_;

};
