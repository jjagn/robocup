#include <Arduino.h>

const int IRin1 = A0;
const int IRin2 = A1;

static int IRRightVal;
static int IRLeftVal;

static int RightProx = 100;
static int LeftProx = 200;

int mode = 0;

int detectObstacle() {
    // takes sensor values from both IR sensors, outputs 1, 2, 3, or 4 for
    // obstacles right, left, all clear or fully obstructed respectively
    IRRightVal = analogRead(IRin1);
    IRLeftVal = analogRead(IRin2);

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