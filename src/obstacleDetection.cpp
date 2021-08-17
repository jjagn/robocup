#include <Arduino.h>

#include "sensorRead.h"

const int IRPinRight = A1;
const int IRPPinLeft = A0;

// CABLES GO INTO CON 3 AND OUT OF CON 1 IF DAISY CHAINING
// OA21 medium range
// 42SK short range

static int IRRightVal;
static int IRLeftVal;

static int RightProx = 200;
static int LeftProx = 200;

int mode = 0;

int detectObstacle() {
    // takes sensor values from both IR sensors, outputs 1, 2, 3, or 4 for
    // obstacles right, left, all clear or fully obstructed respectively

    IRRightVal = readSensors(IRPinRight);
    IRLeftVal = readSensors(IRPPinLeft);

    // IRRightVal = analogRead(IRPinRight);
    // IRLeftVal = analogRead(IRPPinLeft);

    if ((IRRightVal > RightProx) && (IRLeftVal < LeftProx)) {
        Serial.println("Obstacle right");
        return 1;

    } else if ((IRRightVal < RightProx) && (IRLeftVal > LeftProx)) {
        Serial.println("Obstacle left");
        return 2;

    } else if ((IRRightVal < RightProx) && (IRLeftVal < LeftProx)) {
        Serial.println("All clear");
        return 3;

    } else {
        Serial.println("Fully obstructed");
        return 4;

    }
}