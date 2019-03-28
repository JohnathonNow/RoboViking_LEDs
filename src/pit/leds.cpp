#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "leds.h"
#include "../util/util.h"

Adafruit_NeoPixel_ZeroDMA strip(NUMPIXELS, PIN, NEO_GRB);

int set(uint32_t i, int r, int g, int b) {
    if (i >= 0 && i < NUMPIXELS) {
        strip.setPixelColor(i, cap(r), cap(g), cap(b));
    }
}

void rv(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float light = triangle_wave(tim*4/5 + i) * (float)MAX;
        float r = triangle_wave(tim  + i + 0) * light;
        float g = triangle_wave(tim  + i + 32) * light;
        set(i, r, r+g, 0);
    }
}

void rb(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float r = triangle_wave(tim + i) * (float)MAX;
        float g = triangle_wave(tim + i + 25) * (float)MAX;
        float b = triangle_wave(tim + i + 50) * (float)MAX;
        set(i, r, g, b);
    }
    set(tim%NUMPIXELS, 255, 0, 0);
}

void usa(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        int t = (tim * 6 + i) % 540;
        if (t < 180) {
            int r = sind(t) * 255;
            set(i, r, 0, 0);
        } else if (t < 360) {
            int w = sind(t - 180) * 255;
            set(i, w, w, w);
        } else {
            int b = sind(t - 360) * 255;
            set(i, 0, 0, b);
        }
    }
    delay(20);
}

void start() {
    strip.begin();
    strip.setBrightness(cap(BRIGHTNESS*255/100));
    strip.show();
}

void step(uint8_t mode) {
    static uint32_t time = 0;
    usa(time);
    strip.show();
    time++;
}
