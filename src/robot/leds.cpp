#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "leds.h"
#include "../util/util.h"

static Adafruit_NeoPixel_ZeroDMA strip(NUMPIXELS, PIN, NEO_GRB);

static int set(uint32_t i, int r, int g, int b) {
    if (i >= 0 && i < NUMPIXELS) {
        strip.setPixelColor(i, cap(r), cap(g), cap(b));
    }
}

#define NUMPIXELS 300
#define MAX 128


static void rv(uint32_t tim, uint32_t sp) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float r = triangle_wave(tim*sp*5/4  + i + 0) * MAX;
        float g = triangle_wave(tim*sp  + i + 32) * MAX;
        if (i > 188 && i < 255) {
            r /= 2;
            g /= 2;
        }
        set(i, r, r+g, 0);
    }
}

static void rb(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float r = triangle_wave(tim + i) * (float)MAX;
        float g = triangle_wave(tim + i + 25) * (float)MAX;
        float b = triangle_wave(tim + i + 50) * (float)MAX;
        if (i > 160 && i < 255) {
            set(i, r/3, g/3, b/3);
        } else {
            set(i, r, g, b);
        }
    }
}

static void ti(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        int t = (tim * 6 + i) % 540;
        if (t < 180) {
            int r = sind(t) * 255;
            set(i, 0, 0, r);
        } else if (t < 360) {
            int w = sind(t - 180) * 220;
            set(i, w, w, w);
        } else {
            int b = sind(t - 360) * 255;
            set(i, 0, 0, b);
        }
    }
    delay(20);
}

static void usa(uint32_t tim) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        int t = (tim * 6 + i) % 540;
        if (t < 180) {
            int r = sind(t) * 255;
            set(i, r, 0, 0);
        } else if (t < 360) {
            int w = sind(t - 180) * 220;
            set(i, w, w, w);
        } else {
            int b = sind(t - 360) * 255;
            set(i, 0, 0, b);
        }
    }
    delay(20);
}

static void climb(uint32_t time) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        uint32_t r = MAX;
        uint32_t g = MAX;
        uint32_t b = 0;
        if ((time/10 + i) % 6 < 3){
            b = MAX;
            r = 0;
            g = 0;
        }
        set(i, r, g, b);
    }
};

void robot::start() {
    strip.begin();
    strip.setBrightness(cap(BRIGHTNESS*255/100));
    strip.show();
}

void robot::step(uint8_t mode) {
    static uint32_t time = 0;
    /*
    switch (mode) {
        case 0: rb(time); break;
        case 1: rv(time, 1); break;
        case 2: rv(time, 2); break;
        case 3: rv(time, 3); break;
        case 4: climb(time); break;
        case 5: usa(time); break;
        case 6: rb(time); break;
        default: rb(time); break;
    }
    */
    case 0: rv(time, 1);break;
    strip.show();
    time++;
}

