#include "FadeValue.h"

FadeValue::FadeValue() 
    : value(DEFAULT_VALUE), state(FadeState::CONSTANT), 
      startTime(0), duration(0), startValue(0), targetValue(0) {
}

void FadeValue::set(int16_t newValue) {
    value = constrain(newValue, MIN_VALUE, MAX_VALUE);
    state = FadeState::CONSTANT;
}

void FadeValue::on() {
    set(MAX_VALUE);
}

void FadeValue::off() {
    set(0);
}

int16_t FadeValue::getValue() const {
    return value;
}

void FadeValue::fade(uint32_t duration_ms, int16_t target, int16_t start) {
    startTime = millis();
    duration = duration_ms;
    startValue = start;
    targetValue = constrain(target, MIN_VALUE, MAX_VALUE);
    state = FadeState::FADING;
}

void FadeValue::fade(uint32_t duration_ms, int16_t target) {
    this->fade(duration_ms, target, this->value);
}

void FadeValue::update() {
    if (state != FadeState::FADING) {
        return;
    }

    uint32_t elapsedTime = millis() - startTime;
    
    if (elapsedTime >= duration) {
        // Fade is complete
        value = targetValue;
        state = FadeState::CONSTANT;
        return;
    }

    // Use Arduino's map and constrain functions for interpolation
    set(map(elapsedTime, 0, duration, startValue, targetValue));
}

FadeState FadeValue::getState() const {
    return state;
}