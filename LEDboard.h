#pragma once
#include "Adafruit_TLC5947.h"

/*
 * indexes and channel assignments for the TLC5947
 */
#define RGB_FRONT  0 // index of front RGB strip
#define RGB_MIDDLE 1
#define RGB_BACK   2
#define RGB_MOON   3

#define LED_KEY_LEFT  23
#define LED_KEY_RIGHT 22

class LEDboard {
public:
    LEDboard(uint8_t c, uint8_t d, uint8_t l);
    boolean begin();
    void set_front(uint16_t r, uint16_t g, uint16_t b);
    void set_middle(uint16_t r, uint16_t g, uint16_t b);
    void set_back(uint16_t r, uint16_t g, uint16_t b);
    void set_moon(uint16_t r, uint16_t g, uint16_t b);
    void set_key_left(uint16_t v);
    void set_key_right(uint16_t v);
    void off();
private:
    Adafruit_TLC5947 tlc;
};
