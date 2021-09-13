#include <Arduino.h>
#include "sensorRead.h"

#define SENSOR_HEADING_TOLERANCE 10
#define FILTER_PERIOD 10

const int WeightIRPinRight = A3; // lower IR sensor pin
const int WeightIRPinLeft = A2; // lower IR sensor pin

static int WeightIRRightVal;
static int WeightIRLeftVal;

static int RightProx = 100;
static int LeftProx = 100;

int detectWeights() {
    int weightHeading;
    WeightIRRightVal = readSensors(WeightIRPinRight);
    WeightIRLeftVal = readSensors(WeightIRPinLeft);

    if (WeightIRRightVal > RightProx && WeightIRLeftVal > LeftProx) {
        // we have detected a weight, somewhere out there
        weightHeading = WeightIRLeftVal - WeightIRRightVal;
    } else {
        weightHeading = 32767;
    }
    return weightHeading;
}