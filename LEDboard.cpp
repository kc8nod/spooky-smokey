#include "LEDboard.h"

LEDboard::LEDboard(uint8_t c, uint8_t d, uint8_t l) 
    : tlc(1, c, d, l),
      gate(),
      hill1(),
      hill2(),
      moon_r(),
      moon_g(),
      moon_b(),
      key_left(),
      key_right() {
}

boolean LEDboard::begin() {
    return tlc.begin();
}


void LEDboard::update() {
    gate.update();
    hill1.update();
    hill2.update();
    moon_r.update();
    moon_g.update();
    moon_b.update();
    key_left.update();
    key_right.update();
}

void LEDboard::write() {
    tlc.setPWM(LED_GATE, gate.getValue());
    tlc.setPWM(LED_HILL_ONE, hill1.getValue());
    tlc.setPWM(LED_HILL_TWO, hill2.getValue());
    tlc.setPWM(LED_MOON_RED, moon_r.getValue());
    tlc.setPWM(LED_MOON_GREEN, moon_g.getValue());
    tlc.setPWM(LED_MOON_BLUE, moon_b.getValue());
    tlc.setPWM(LED_KEY_LEFT, key_left.getValue());
    tlc.setPWM(LED_KEY_RIGHT, key_right.getValue());

    tlc.write();
}

void LEDboard::off() {
    for(int i=0; i<24; i++) {
        tlc.setLED(i, 0, 0, 0);
    }
    tlc.write();
}