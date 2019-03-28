#include "src/pit/leds.h"
#include "src/util/mode.h"

void setup() {
    Serial.begin(9600);
    start();
}

void loop() {
    step(mode());
}
