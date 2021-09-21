#include <Arduino.h>
#include <Servo.h>

#include <TimerOne.h>

#include "obstacleDetection.h"
#include "motorControl.h"
#include "weightDetection.h"
#include "robostruct.h"
#include "pickup.h"

#define WEIGHT_DETECTION_ANGULAR_TOLERANCE 50

#define KNOCK_O_CLOCK 6000000

#define TIMER_UPDATE_FREQ 1000
#define TIMER_INTERRUPT_PERIOD 1000000 / SCAN_RATE_HZ

#define SCAN_RATE_HZ 10
#define SCAN_PRESCALER TIMER_UPDATE_FREQ / SCAN_RATE_HZ

#define POLL_RATE 100
#define DELAY 1000 / POLL_RATE

int weightHeading;
int IRResult;
int mode = 0;
bool weightPresent = false;
int weightCollectTimeOut = 0;
unsigned long roundStartTime = 0;

volatile int scan = 0;
volatile bool scanFlag = false;

struct Robostruct Robot;

void TimerHandler() {
    if (++scan > SCAN_PRESCALER) {
        scanFlag = true;
        scan = 0;
    }
}

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    
    // Init timer ITimer1
    Timer1.initialize(TIMER_INTERRUPT_PERIOD);
    Timer1.attachInterrupt(TimerHandler);

    roundStartTime = millis();

    initMotors();
    initPickup();
}

void loop() {
    runStepper();

    if (scanFlag) {
            scanFlag = false;
            weightHeading = detectWeights(); // scan lower sensors to see if there is a weight present
            IRResult = detectObstacle(); // take input from IR reading function
    }

    switch(Robot.mode) {
        case (0): // SEARCHING FOR WEIGHTS
            if (weightHeading == 32767) { // i.e. whatever output from detectWeights means there are no weights
                Robot.mode = 0;
            } else {
                Robot.mode = 1; // we got one
            }

            motorControl(IRResult); // control motors based on sensor output

            break;
        
        case(1): // WEIGHT DETECTED, MOVING TO PICKUP
            //weightPresent = readProximity(); // check whether there is a weight in the pickup area

            Robot.weightCollectTimeout++;

            if (Robot.weightCollectTimeout > Robot.weightCollectTimeoutLimit) {
                Robot.resetTimeout();
                Robot.mode = 0;
                // Serial.println("aborting pickup");
            }
            // while weight is not in detection zone/if weight is not in detection zone
            // as long as the weight is not just a wall
            if (!weightPresent) {
                if (weightHeading > WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnRight();
                } else if (weightHeading < -WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnLeft();
                } else {
                    creep();
                }
            } else {
                pickup(); // this function should turn on the magnet, lift it, drop the weight into the bin, and return the magnet to zero
                Robot.mode = 0;
                Robot.collectedWeights++;
            }


                break;
    }
}
