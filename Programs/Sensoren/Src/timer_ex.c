#include "timer_ex.h"
#include "timer.h"
#include "errorhandler.h"
#include <stdint.h>

#define MAX_US (UINT32_MAX / TICKS_PER_US)

double getTimeFrame(uint32_t start, uint32_t end) {
    double frame = (start > end) ? (UINT32_MAX - start + end) : (end - start);
    return (frame / TICKS_PER_US);
}

int sleep(uint32_t us) {
    uint32_t start = getTimeStamp();
    if (us > MAX_US) return NOK;

    while ( us > getTimeFrame(start, getTimeStamp()) ) ;
    return EOK;
}

// EOF
