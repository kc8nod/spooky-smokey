#pragma once
#include "Adafruit_TLC5947.h"
#include "FadeValue.h"


// Current setting resistor
// add the indicated resistor to get the approximate output current
// empty - 15mA
// 9.1k. - 20mA
// 4.7k  - 25mA
// 3.3k. - 30mA


/*
 * indexes and channel assignments for the TLC5947
 */
#define LED_MOON_RED 9
#define LED_MOON_BLUE 10
#define LED_MOON_GREEN 11

#define LED_GATE  0
#define LED_HILL_ONE 1
#define LED_HILL_TWO 2
#define LED_KEY_RIGHT 22
#define LED_KEY_LEFT  23

class LEDValue : public FadeValue {
public:
    static const int MAX_VALUE = 4095;  // Override parent's MAX_VALUE
    static const int MIN_VALUE = 0;     // Minimum value for LED brightness
    
    // Constructor - can use parent's constructor
    using FadeValue::FadeValue;
};

class LEDboard {
public:
    LEDboard(uint8_t c, uint8_t d, uint8_t l);
    boolean begin();
    LEDValue gate;
    LEDValue hill1;
    LEDValue hill2;
    LEDValue moon_r;
    LEDValue moon_g;
    LEDValue moon_b;
    LEDValue key_left;
    LEDValue key_right;

    void update();
    void off();
    void write();
private:
    Adafruit_TLC5947 tlc;
};
