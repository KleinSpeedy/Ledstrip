/* Global Includes */

/* Local Includes */
#include "ChristmasEffect.h"

ChristmasEffect::ChristmasEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

#define TIMES_PER_SECOND(x) EVERY_N_MILLISECONDS(1000/x)

void ChristmasEffect::draw()
{
    TIMES_PER_SECOND(50)
    {
        float scroll = 0.0f;
        scroll += 0.1f;
        if (scroll > 5.0f)
            scroll -= 5.0f;

        for (float i = scroll; i < NUM_LEDS/2 - 1; i += 5)
        {
            drawPixels(i, 3, CRGB::Green);
            drawPixels(NUM_LEDS-1-(int)i, 3, CRGB::Red);
        }
    }
    /*
    TIMES_PER_SECOND(50)
    {
      fadeToBlackBy(ledStrip_, NUM_LEDS, 64);
      float pos = beatsin16(32, 0, NUM_LEDS-10);
      byte hue = beatsin8(32, 0, 255);
      drawPixels(pos, 10, CHSV(hue, 255, 255));
    }
    */
}

// FractionalColor
//
// Returns a fraction of a color; abstracts the fadeToBlack away so that we can later
// do better color correction as needed
CRGB ChristmasEffect::colorFraction(const CRGB colorIn, float fraction)
{
  fraction = min(1.0f, fraction);
  return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

// DrawPixels
//
// Draw a sub-pixel precise amount of pixels starting at a floating point offset; for example
// you can draw 2.75 pixels starting a 5.5, and it will end at 8.25
void ChristmasEffect::drawPixels(float fPos, float count, CRGB color)
{
    // Figure out how much the first pixel will hold
    float availFirstPixel = 1.0f - (fPos - (long)(fPos));  // If we are starting at 2.25, there would be 0.75 avail here
    float amtFirstPixel = min(availFirstPixel, count);     // But of course we never draw more than we need
    float remaining = min(count, FastLED.size()-fPos);     // How many pixels remain after we draw the front header pixel
    int iPos = fPos;

    // Blend (add) in the color value of this first partial pixel ...and decrement the remaining pixel count by that same amount

    if (remaining > 0.0f)
    {
      FastLED.leds()[iPos++] += colorFraction(color, amtFirstPixel); 
      remaining -= amtFirstPixel;                          
    }

    // Draw any full pixels and stop when we have a full pixel or less remainining

    while (remaining > 1.0f)                               // Final pixel can 'handle' up to 1.0 full pixels, so we draw anything more here
    {
      FastLED.leds()[iPos++] += color;                     // Draw them in one at aa time and update the remaining counts
      remaining--;
    }  

    // Draw tail pixel, up to a single full pixel

    if (remaining > 0.0f)  
    {                    
        FastLED.leds()[iPos] += colorFraction(color, remaining);     
    }
}