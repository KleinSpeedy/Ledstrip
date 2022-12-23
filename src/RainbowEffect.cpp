/* Global Includes */

/* Local Includes */
#include "RainbowEffect.h"

// Gradient palette "rainbow_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/rc/tn/rainbow.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 48 bytes of program space.

DEFINE_GRADIENT_PALETTE( rb_gp ) {
    0, 126,  1,142,
   25, 171,  1, 26,
   48, 224,  9,  1,
   71, 237,138,  1,
   94,  52,173,  1,
  117,   1,201,  1,
  140,   1,211, 54,
  163,   1,124,168,
  186,   1,  8,149,
  209,  12,  1,151,
  232,  12,  1,151,
  255, 171,  1,190
};

CRGBPalette16 rainbow_gp = rb_gp;

RainbowEffect::RainbowEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

void RainbowEffect::draw()
{
    fill_palette(stretchedStrip.data(), stretchedStrip.size(), index++, 0, rainbow_gp, 255, LINEARBLEND);
    EVERY_N_MILLISECONDS(25)
    {
        for(int i = 0; i < NUM_LEDS; i++)
        {
            ledStrip_[i] = stretchedStrip.at(i);
        }
    }
}