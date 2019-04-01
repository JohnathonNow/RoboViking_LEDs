#include <Adafruit_NeoPixel_ZeroDMA.h>
#include "leds.h"
#include "../util/util.h"

static Adafruit_NeoPixel_ZeroDMA strip(NUMPIXELS, PIN, NEO_GRB);

static bool is_front_cart(uint32_t i) {
    return i > 188 && i < 255;
}

static int set(uint32_t i, int r, int g, int b) {
    if (i >= 0 && i < NUMPIXELS) {
        strip.setPixelColor(i, cap(r), cap(g), cap(b));
    }
}

static void rv(uint32_t tim, uint32_t sp) {
    for (uint32_t i = 0; i < NUMPIXELS; i++) {
        float r = triangle_wave(tim*sp*5/4  + i + 0) * MAX;
        float g = triangle_wave(tim*sp  + i + 32) * MAX;
        if (is_front_cart(i)) {
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
        if (is_front_cart(i)) {
            set(i, r/2, g/2, b/2);
        } else {
            set(i, r, g, b);
        }
    }
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

void cart::start() {
    strip.begin();
    strip.setBrightness(cap(BRIGHTNESS*255/100));
    strip.show();
}

void cart::step(uint8_t mode) {
    static uint32_t time = 0;
    rv(time, 1);
    strip.show();
    time++;
}

