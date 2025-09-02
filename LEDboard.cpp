#include "LEDboard.h"

LEDboard::LEDboard(uint8_t c, uint8_t d, uint8_t l) 
    : tlc(1, c, d, l),
      gate(),
      hill1(),
      hill2(),
      moon(),
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
    moon.update();
    key_left.update();
    key_right.update();
}

void LEDboard::write() {
    tlc.setPWM(LED_GATE, gate.getValue());
    tlc.setPWM(LED_HILL_ONE, hill1.getValue());
    tlc.setPWM(LED_HILL_TWO, hill2.getValue());
    tlc.setLED(LED_MOON_IDX, moon.red.getValue(), moon.green.getValue(), moon.blue.getValue());
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

void MoonValue::set(int r, int g, int b) {
    red.set(r);
    green.set(g);
    blue.set(b);
}

void MoonValue::fade(int duration, int r, int g, int b) {
    red.fade(duration, r);
    green.fade(duration, g);
    blue.fade(duration, b);
}

void MoonValue::fade_pct(int duration, int p) {
    int v = red.percent(p);
    fade(duration, v, v, v);
}

void MoonValue::update() {
    red.update();
    green.update();
    blue.update();
}

void MoonValue::set_pct(int p) {
    int v = red.percent(p);
    set(v, v, v);
}
