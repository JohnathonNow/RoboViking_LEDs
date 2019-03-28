#ifndef LEDS_H
#define LEDS_H

#define PIN        (4)
#define NUMPIXELS  (600)

#define MIN        (0)
#define MAX        (255)
#define BRIGHTNESS (60)

void start();
void step(uint8_t mode);

#endif
