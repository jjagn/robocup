#ifndef ROBOSTRUCT_H
#define ROBOSTRUCT_H

typedef struct Robostruct {
    int mode = 0;
    bool weightPresent = false;
    int weightCollectTimeout;
    int weightCollectTimeoutLimit = 1000;
    int collectedWeights = 0;
    int weightGoal = 3;

    int weightHeading;
    int IRResult;
    int weightCollectTimeOut = 0;
    volatile int scan = 0;
    volatile bool scanFlag = false;

    void resetTimeout(void) {
        weightCollectTimeout = 0;
    }

} robostruct;

#endif