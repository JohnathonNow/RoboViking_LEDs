#include "src/pit/leds.h"
#include "src/robot/leds.h"
#include "src/cart/leds.h"
#include "src/util/mode.h"

using namespace pit;

void setup() {
    start();
}

void loop() {
    step(mode());
}
