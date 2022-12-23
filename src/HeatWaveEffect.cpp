/* Global Includes */

/* Local Includes */
#include "HeatWaveEffect.h"

/* Taken from css-gradient.io */
DEFINE_GRADIENT_PALETTE (hw_gp)
{
    0,   255, 164,   0, // slightly bright orange
    64,  247, 207, 115, // skin colorish
    128, 255,  87,   0, // dark orange
    192, 255, 255,  59, // yellowish
    255, 255, 100,   0  // slightly dark orange

};

// Gradient palette "SummerSunset_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/nd/atmospheric/tn/SummerSunset.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE( sumSun_gp ) {
    0, 163, 23,  1,
   33, 206, 34,  5,
   70, 255, 48, 17,
   95, 255, 45, 31,
  100, 255, 44, 52,
  106, 249, 40, 23,
  122, 244, 37,  7,
  137, 249, 65,  6,
  163, 255,100,  4,
  207, 100, 44,  3,
  255,  22, 11,  3
};


CRGBPalette16 heatWave_gp = hw_gp;
CRGBPalette16 summerSun_gp = sumSun_gp;

HeatWaveEffect::HeatWaveEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

void HeatWaveEffect::draw()
{
    fill_palette(ledStrip_, NUM_LEDS, index_, 1, summerSun_gp, 255, LINEARBLEND);

    EVERY_N_MILLISECONDS(25)
    {
        index_++;
    }
}