#include <Arduino.h>
#include "sensorRead.h"

#define SENSOR_HEADING_TOLERANCE 10
#define FILTER_PERIOD 10

const int IRPinRight = A0; // lower IR sensor pin
const int IRPinLeft = A1; // lower IR sensor pin

static int IRRightVal;
static int IRLeftVal;

static int RightProx = 100;
static int LeftProx = 200;

int detectWeights() {
    int weightHeading;
    IRRightVal = readSensors(IRPinRight);
    IRLeftVal = readSensors(IRPinLeft);

    if (IRRightVal > RightProx && IRLeftVal > LeftProx) {
        // we have detected a weight, somewhere out there
        weightHeading = IRRightVal - IRLeftVal;
    }
    return weightHeading;
}