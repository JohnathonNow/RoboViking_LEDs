#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "leds.h"
#include "../util/util.h"

static Adafruit_NeoPixel_ZeroDMA strip(NUMPIXELS, PIN, NEO_GRB);

static int set(uint32_t i, int r, int g, int b) {
    if (i >= 0 && i < NUMPIXELS) {
        strip.setPixelColor(i, cap(r), cap(g), cap(b));
    }
}

static void rv(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float light = triangle_wave(tim*4/5 + i) * (float)MAX;
        light = 255;
        float r = triangle_wave(tim*5/4  + i + 0) * light;
        float g = triangle_wave(tim  + i + 32) * light;
        set(i, r, r+g, 0);
    }
}

static void rb(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float r = triangle_wave(tim + i) * (float)MAX;
        float g = triangle_wave(tim + i + 25) * (float)MAX;
        float b = triangle_wave(tim + i + 50) * (float)MAX;
        set(i, r, g, b);
    }
    set(tim%NUMPIXELS, 255, 0, 0);
}

static void usa(uint32_t tim) {
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

static void mich(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        int t = (tim * 6 + i) % 540;
        if (t < 270) {
            int r = sind(t) * 255;
            set(i, r, 0, 0);
        } else {
            int rg = sind(t - 270) * 255;
            set(i, rg, rg, 0);
        }
    }
    delay(20);
}

static void climb(uint32_t time) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        uint32_t r = 128;
        uint32_t g = 128;
        uint32_t b = 0;
        if ((time/10 + i) % 6 < 3){
            r = 0;
        }
        set(i, r, g, b);
    }
};

void pit::start() {
    strip.begin();
    strip.setBrightness(cap(BRIGHTNESS*255/100));
    strip.show();
}

void pit::step(uint8_t mode) {
    static uint32_t time = 0;
    rv(time);
    strip.show();
    time++;
}
