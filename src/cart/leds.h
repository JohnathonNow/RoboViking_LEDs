#ifndef ROBOT_H
#define ROBOT_H

#define PIN        (4)
#define NUMPIXELS  (300)

#define MIN        (0)
#define MAX        (128)
#define BRIGHTNESS (100)

namespace cart {
    void start();
    void step(uint8_t mode);
}

#endif
