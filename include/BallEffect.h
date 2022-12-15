#pragma once
/* Global Includes */
#include <sys/time.h>
#include <vector>
#include <array>

/* Local Includes */
#include "EffectInterface.h"

class BallEffect : public EffectInterface
{
public:
    BallEffect(uint8_t encoding, 
        CRGB *ledStrip, 
        size_t length, 
        size_t count, 
        uint8_t fade, 
        bool mirrored);

    void draw() override;

private:
    uint8_t encoding_;

    size_t stripLength_;
    size_t numBalls_;
    uint8_t fadeRate_;

    bool mirrored_;

    double initialBallSpeed(double height) const;

    static double time();

    std::array<CRGB, 5> colors = {
        CRGB::Green,
        CRGB::Red,
        CRGB::Blue,
        CRGB::Orange,
        CRGB::Indigo
    };

    /* contain informations for each ball */
    std::vector<double> timeAtLastBounce_, heigth_, ballSpeed_, dampening_;
    /* whats the ball color */
    std::vector<CRGB> ballColor_;

    /* Constants */
    static constexpr double Gravity = -9.81;
    static constexpr double StartHeight = 1.0;

    const double ImpactVelocity = initialBallSpeed(StartHeight);
};
