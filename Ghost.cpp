#include "Ghost.h"

Ghost::Ghost(int pin) {
    servo.attach(pin);
    update();
}

void Ghost::set(int s) {
    speed.set(s);
}

void Ghost::ramp(int duration, int target) {
    speed.fade(duration, target);
}

void Ghost::update() {
    speed.update();
    servo.write(speed.getValue());
}

void Ghost::stop() {
    speed.set(speed.DEFAULT_VALUE);
    update();
}

