#ifndef ROBOSTRUCT_H
#define ROBOSTRUCT_H

#include "debug.h"

typedef struct Robostruct {
    int mode = 0;
    bool weightPresent = false;
    unsigned int weightCollectTimeout = 0;
    unsigned int weightCollectTimeoutLimit = 10000;
    int collectedWeights = 0;
    int weightGoal = 3;
    int zeroState = 0;
    int pickupState = 0;
    int abortTimer1 = 0;
    int abortTimer2 = 0;
    unsigned int abortLimit1 = 500;
    unsigned int abortLimit2 = 500;

    bool zeroed = false;

    int weightHeading;
    int IRResult;
    volatile int scan = 0;
    volatile bool scanFlag = false;

    void CheckTimeout() {
        static bool first_check = true;
        static unsigned long startTime;

        if (first_check) {
            startTime = millis();
            first_check = false;
        }

        unsigned long timeNow = millis();

        unsigned long currentTime = timeNow-startTime;

        if (currentTime > weightCollectTimeoutLimit) {
                    weightCollectTimeout = 0;
                    mode = 5;
                    debugln("aborting pickup");
                    first_check = true;
                }
    }

} robostruct;

#endif