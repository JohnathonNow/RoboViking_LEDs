#include <Arduino.h>
#include "mode.h"

uint8_t mode() {
    static uint8_t loaded = 0;
    uint8_t pins[] = PINS;
    if (!loaded) {
        for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++) {
            pinMode(pins[i], INPUT);
        }
        loaded = 1;
    }
    uint8_t out = 0;
    for (uint8_t i = 0; i < sizeof(pins)/sizeof(uint8_t); i++) {
        out |= (digitalRead(pins[i])&1)<<i;
    }

    return out;
}
