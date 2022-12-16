/* Global Includes */

/* Local Includes */
#include "BallEffect.h"

BallEffect::BallEffect(uint8_t encoding, CRGB *ledStrip, size_t length, size_t ballCount, uint8_t fade, bool mirrored)
: stripLength_(length - 1),
    numBalls_(ballCount),
    fadeRate_(fade),
    mirrored_(mirrored),
    timeAtLastBounce_(ballCount),
    heigth_(ballCount),
    ballSpeed_(ballCount),
    dampening_(ballCount),
    ballColor_(ballCount)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);

    for(size_t i = 0; i < ballCount; i++)
    {
        heigth_[i]              = StartHeight;  // current ball height
        timeAtLastBounce_[i]    = time();   // when ball last hit the ground
        dampening_[i]           = 0.90 - i / pow(numBalls_, 2); // bouncines of this ball
        ballSpeed_[i]           = initialBallSpeed(heigth_[i]); // dont dampen the initial launch
        ballColor_[i]           = colors[i % colors.size()]; // wrap arround the colors
    }
}

void BallEffect::draw()
{
    if(fadeRate_ != 0)
    {
        for(size_t i = 0; i < stripLength_; i++)
        {
            ledStrip_[i].fadeToBlackBy(fadeRate_);
        }
    }
    else
    {
        FastLED.clear();
    }

    for(size_t i = 0; i < numBalls_; i++)
    {
        double timeSinceLastBounce = (time() - timeAtLastBounce_[i]) / 4.0;

        // use standard constant acceleration
        heigth_[i] = 0.5 * Gravity * pow(timeSinceLastBounce, 2.0) + ballSpeed_[i] * timeSinceLastBounce;

        // Ball hits the ground - let it bounce
        if(heigth_[i] < 0)
        {
            heigth_[i] = 0;
            ballSpeed_[i] = dampening_[i] * ballSpeed_[i];
            timeAtLastBounce_[i] = time();

            if(ballSpeed_[i] < 0.01)
            {
                ballSpeed_[i] = initialBallSpeed(StartHeight) * dampening_[i];
            }
        }

        size_t position = (size_t)(heigth_[i] * (stripLength_ -1) / StartHeight);

        ledStrip_[position] += ballColor_[i];
        ledStrip_[position + 1] += ballColor_[i];

        if(mirrored_)
        {
            ledStrip_[stripLength_ - 1 - position] += ballColor_[i];
            ledStrip_[stripLength_ - position] += ballColor_[i];
        }
    }
    delay(20);
}
