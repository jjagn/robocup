#ifndef ROBOSTRUCT_H
#define ROBOSTRUCT_H

#include "debug.h"

typedef struct Robostruct {
    int mode = 0;
    bool weightPresent = false;
    int weightCollectTimeout = 0;
    int weightCollectTimeoutLimit = 1000;
    int collectedWeights = 0;
    int weightGoal = 3;
    int zeroState = 0;
    int pickupState = 0;

    int weightHeading;
    int IRResult;
    volatile int scan = 0;
    volatile bool scanFlag = false;

    void resetTimeout(void) {
        weightCollectTimeout = 0;
    }

    void CheckTimeout() {
    if (++this->weightCollectTimeout > this->weightCollectTimeoutLimit) {
                this->resetTimeout();
                this->mode = 0;
                debugln("aborting pickup");
            }
}

} robostruct;

#endif