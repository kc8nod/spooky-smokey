#include "LEDboard.h"

#include "LEDboard.h"

LEDboard::LEDboard(uint8_t c, uint8_t d, uint8_t l) : tlc(1, c, d, l) {
    // Constructor implementation
}

boolean LEDboard::begin() {
    return tlc.begin();
}

void LEDboard::set_gate(uint16_t v) {
    tlc.setPWM(LED_GATE, v);
    tlc.write();
}
void LEDboard::set_hill1(uint16_t v) {
    tlc.setPWM(LED_HILL_ONE, v);
    tlc.write();
}
void LEDboard::set_hill2(uint16_t v) {
    tlc.setPWM(LED_HILL_TWO, v);
    tlc.write();
}

void LEDboard::set_moon(uint16_t r, uint16_t g, uint16_t b) {
    tlc.setLED(RGB_MOON, r, g, b);
    tlc.write();
}
void LEDboard::set_key_left(uint16_t v) {
    tlc.setPWM(LED_KEY_LEFT, v);
    tlc.write();
}
void LEDboard::set_key_right(uint16_t v) {
    tlc.setPWM(LED_KEY_RIGHT, v);
    tlc.write();
}

void LEDboard::off() {
    for(int i=0; i<24; i++) {
        tlc.setLED(i, 0, 0, 0);
    }
    tlc.write();
}