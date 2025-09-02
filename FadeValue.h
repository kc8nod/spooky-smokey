#pragma once
#include <Arduino.h>

enum class FadeState {
    FADING,
    CONSTANT
};

class FadeValue {
public:
    FadeValue();
    void set(int16_t value);
    void on();
    void off();
    int16_t getValue() const;
    void fade(uint32_t duration_ms, int16_t targetValue, int16_t startValue);
    void fade(uint32_t duration_ms, int16_t targetValue);
    void update();
    FadeState getState() const;

private:
    int16_t value;
    static const int16_t MAX_VALUE =  32767;
    static const int16_t MIN_VALUE = -32768;
    static const int16_t DEFAULT_VALUE = 0;
    
    FadeState state;
    uint32_t startTime;
    uint32_t duration;
    int16_t startValue;
    int16_t targetValue;
};
