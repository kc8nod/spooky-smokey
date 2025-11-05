#pragma once
#include "FadeValue.h"
#include <Servo.h>

class GhostValue : public FadeValue {
public:
    static const int MAX_VALUE = 180;  // Override parent's MAX_VALUE
    static const int MIN_VALUE = 0;     // Minimum value for LED brightness
    static const int DEFAULT_VALUE = 90; // Default to STOP position
    
    // Constructor - can use parent's constructor
    using FadeValue::FadeValue;
};

class Ghost {
public:

private:
    GhostValue speed;
    Servo servo;

public:
    Ghost(int pin);
    void update();
    void set(int speed);
    void set_pct(int p);
    void ramp(int duration, int target);
    void ramp_pct(int duration, int p);
    void stop();
};
