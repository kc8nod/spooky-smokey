#pragma once
#include "FadeValue.h"
#include <Servo.h>

class GhostValue {
public:
    
};

class Ghost {

  private:
    static const int MAX_VALUE = 180;  // Override parent's MAX_VALUE
    static const int MIN_VALUE = 0;     // Minimum value for LED brightness

    FadeValue speed;
    int zeroPosition;
    Servo servo;

    int speedValue(int pct);

  public:
    Ghost(int pin, int zeroPosition);
    void update();
    void set_pct(int p);
    void ramp_pct(int duration, int p);
    void stop();
};
