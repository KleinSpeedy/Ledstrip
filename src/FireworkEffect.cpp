/* Global Includes */

/* Local Includes */
#include "FireworkEffect.h"

FireworkEffect::FireworkEffect(uint8_t encoding, CRGB *ledStrip)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);
};

void FireworkEffect::draw()
{
  EVERY_N_MILLISECONDS(10)
  {
    if(!flareShot[0])
      shoot(0);
    if(!flareShot[1])
      shoot(1);
    if(!flareShot[2])
      shoot(2);
  }
  EVERY_N_MILLISECONDS(10)
  {
    if(flareShot[0])
      doSparks(0);
    if(flareShot[1])
      doSparks(1);
    if(flareShot[2])
      doSparks(2);
  }
  
  EVERY_N_MILLISECONDS(10)
  {
    fadeToBlackBy(ledStrip_, NUM_LEDS, 80);
  }
}

void FireworkEffect::shoot(byte nr)
{
  if (random(1000) < 10)
  {
    flareShot[nr] = true;
    flarePos[nr] = random(40, NUM_LEDS - 40);
    nSparks[nr] = 30;
    // initialize sparks
    for (int x = 0; x < nSparks[nr]; x++)
    {
      sparkPos[nr][x] = flarePos[nr] << 7;
      sparkVel[nr][x] = random16(0, 5120) - 2560; // velocitie original -1 o 1 now -255 to + 255
      word sph = abs(sparkVel[nr][x]) << 2;
      if (sph > 2550)
        sph = 2550; // set heat before scaling velocity to keep them warm heat is 0-500 but then clamped to 255
      sparkHeat[nr][x] = sph;
    }
    sparkHeat[nr][0] = 5000; // this will be our known spark
  }
}

void FireworkEffect::doSparks(byte nr)
{
  for (int x = 0; x < nSparks[nr]; x++)
  {
    sparkPos[nr][x] = sparkPos[nr][x] + (sparkVel[nr][x] >> 5); // adjust speed of sparks here
    sparkPos[nr][x] = constrain(sparkPos[nr][x], 0, maxPos);
    sparkHeat[nr][x] = scale16(sparkHeat[nr][x], 64000); // adjust speed of cooldown here
    CRGB color;
    if (nr == 0)
      color = ColorFromPalette(gPal1_, scale16(sparkHeat[nr][x], 6600));
    if (nr == 1)
      color = ColorFromPalette(gPal2_, scale16(sparkHeat[nr][x], 6600));
    if (nr == 2)
      color = ColorFromPalette(gPal3_, scale16(sparkHeat[nr][x], 6600));
    
    ledStrip_[sparkPos[nr][x] >> 7] += color;
    if (sparkHeat[nr][0] < 1)
    {
      flareShot[nr] = false; // this fireworks is done
    }
  }
}
