#ifndef ROBOSTRUCT_H
#define ROBOSTRUCT_H

#include "debug.h"

typedef struct Robostruct {
    int mode = 0;
    bool weightPresent = false;
    int weightCollectTimeout = 0;
    int weightCollectTimeoutLimit = 100;
    int collectedWeights = 0;
    int weightGoal = 3;
    int zeroState = 0;
    int pickupState = 0;
    int abortTimer1 = 0;
    int abortTimer2 = 0;
    int abortLimit1 = 100;
    int abortLimit2 = 100;

    bool zeroed = false;

    int weightHeading;
    int IRResult;
    volatile int scan = 0;
    volatile bool scanFlag = false;

    void CheckTimeout() {
    if (++weightCollectTimeout > weightCollectTimeoutLimit) {
                weightCollectTimeout = 0;
                mode = 0;
                debugln("aborting pickup");
            }
}

} robostruct;

#endif