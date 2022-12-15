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
    
};
