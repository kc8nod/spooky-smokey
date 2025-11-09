#include "Ghost.h"

Ghost::Ghost(int pin, int zeroPosition) {
    this->zeroPosition = zeroPosition;
    speed.set(zeroPosition);
    servo.attach(pin);
    update();
}

int Ghost::speedValue(int pct) {
    if(pct>0){
        return map(pct, 0, 100, zeroPosition, Ghost::MAX_VALUE);
    }else{
        return map(pct, -100, 0, Ghost::MIN_VALUE, zeroPosition);
    }
}

void Ghost::set_pct(int p) {
    speed.set(speedValue(p));
}

void Ghost::ramp_pct(int duration, int p) {
    speed.fade(duration, speedValue(p));
}

void Ghost::update() {
    speed.update();
    servo.write(speed.getValue());
}

void Ghost::stop() {
    speed.set(zeroPosition);
    update();
}

