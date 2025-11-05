#include "Ghost.h"

Ghost::Ghost(int pin) {
    servo.attach(pin);
    update();
}

void Ghost::set(int s) {
    speed.set(s);
}

void Ghost::set_pct(int p) {
    int s = map(p, -100, 100, GhostValue::MIN_VALUE, GhostValue::MAX_VALUE);
    speed.set(s);
}

void Ghost::ramp(int duration, int target) {
    speed.fade(duration, target);
}

void Ghost::ramp_pct(int duration, int p) {
    int s = map(p, -100, 100, GhostValue::MIN_VALUE, GhostValue::MAX_VALUE);
    speed.fade(duration, s);
}

void Ghost::update() {
    speed.update();
    servo.write(speed.getValue());
}

void Ghost::stop() {
    speed.set(speed.DEFAULT_VALUE);
    update();
}

