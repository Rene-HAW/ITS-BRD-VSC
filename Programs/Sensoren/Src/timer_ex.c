#include "timer_ex.h"
#include "timer.h"
#include <stdint.h>

#define US_LIMIT (UINT32_MAX / TICKS_PER_US - 1000)

double getTimeFrame(uint32_t start, uint32_t end) {
    double frame = (start > end) ? (UINT32_MAX - start + end) : (end - start);
    return (frame / TICKS_PER_US);
}

void sleep(double us) {
    uint32_t now, start = getTimeStamp();
    double usPassed = 0;

    while (us > usPassed) {
        if (usPassed > US_LIMIT) {
            start = now;
            us -= usPassed;
        }
        now = getTimeStamp();
        usPassed = getTimeFrame(start, now);
    }
}

// EOF
