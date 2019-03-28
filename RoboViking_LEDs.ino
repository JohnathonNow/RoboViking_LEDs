#include "src/pit/leds.h"

void setup() {
    Serial.begin(9600);
    start();
}

void loop() {
    step(0);
}
