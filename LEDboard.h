#pragma once
#include "Adafruit_TLC5947.h"


// Current setting resistor
// add the indicated resistor to get the approximate output current
// empty - 15mA
// 9.1k. - 20mA
// 4.7k  - 25mA
// 3.3k. - 30mA


/*
 * indexes and channel assignments for the TLC5947
 */
#define RGB_MOON   3

#define LED_GATE  0
#define LED_HILL_ONE 1
#define LED_HILL_TWO   2
#define LED_KEY_RIGHT 22
#define LED_KEY_LEFT  23

class LEDboard {
public:
    LEDboard(uint8_t c, uint8_t d, uint8_t l);
    boolean begin();
    void set_gate(uint16_t v);
    void set_hill1(uint16_t v);
    void set_hill2(uint16_t v);
    void set_moon(uint16_t r, uint16_t g, uint16_t b);
    void set_key_left(uint16_t v);
    void set_key_right(uint16_t v);
    void off();
private:
    Adafruit_TLC5947 tlc;
};
