/* Global Includes */

/* Local Includes */
#include "BallEffect.h"

BallEffect::BallEffect(uint8_t encoding, CRGB *ledStrip, size_t length, size_t count, uint8_t fade, bool mirrored)
: stripLength_(length - 1),
    numBalls_(count),
    fadeRate_(fade),
    mirrored_(mirrored),
    timeAtLastBounce_(count),
    heigth_(count),
    ballSpeed_(count),
    dampening_(count),
    ballColor_(count)
{
    setEncoding(encoding);
    setLedStrip(ledStrip);

    for(size_t i = 0; i < numBalls_; i++)
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

            size_t position = (size_t)(heigth_[i] * (stripLength_ -1) / StartHeight);

            ledStrip_[stripLength_] = ballColor_[i];
            ledStrip_[stripLength_ + 1] = ballColor_[i];

            if(mirrored_)
            {
                ledStrip_[stripLength_ - 1 - position] = colors[i];
                ledStrip_[stripLength_ - position] = colors[i];
            }
            
        }
    }
    delay(20);
}

double BallEffect::initialBallSpeed(double height) const
{
    return sqrt(-2 * Gravity * height);
}

double BallEffect::time()
{
    timeval tv = { 0 };
    gettimeofday(&tv, nullptr);
    return (double)(tv.tv_usec / 100000.0 + (double) tv.tv_sec);
}