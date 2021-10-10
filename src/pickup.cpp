// pickup.c - module for controlling weight pickup;
#include <Arduino.h>
#include <AccelStepper.h>
#include "debug.h"

#define RAISE 1
#define LOWER 0
#define TIMEOUT_LIMIT 1000
#define MICROSTEP 1

#define MAX_SPEED 1000*MICROSTEP
#define MAX_ACCELERATION 1000*MICROSTEP
#define IDLE_POSITION -5000*MICROSTEP
#define DROPOFF_POSITION -6500*MICROSTEP
#define ZERO_FORWARD_TARGET 10000*MICROSTEP
#define ZERO_REAR_TARGET -5000*MICROSTEP

const int electromagnetPin = 34;
const int stepPin = 42;
const int dirPin = 43;
const int lowerLimitSwitch = 38;
const int inductiveProx = A5;
const int carriageContactSwitch = 39;

// NOTE: LIMIT SWITCHES ARE ACTIVE LOW

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void initPickup(void) {
    pinMode(electromagnetPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    stepper.setMaxSpeed(MAX_SPEED);
    stepper.setAcceleration(MAX_ACCELERATION);
}

void moveStepper(long target) {
    stepper.moveTo(target);
}

void runStepper(void) {
    // runs the stepper motor to make sure it is updating every loop
    stepper.run();
}

void moveStepperToLimit(int limitSwitch) {
    // man i hope this doesn't break stuff terribly
    while (digitalRead(limitSwitch) == 0) {
        stepper.run();
    }
}

void cycle() {
    if (stepper.currentPosition() <= 0)
        stepper.moveTo(ZERO_FORWARD_TARGET);
    else if (stepper.currentPosition() >= ZERO_FORWARD_TARGET)
        stepper.moveTo(0);
}

void enableMagnet(void) {
    // for debugging at the moment but who knows?
    digitalWrite(electromagnetPin, 1);
}

void disableMagnet(void) {
    // see above
    digitalWrite(electromagnetPin, 0);
}

void pickup(int* state) {
    // pick up weight
    // TODO: NEEDS TO BE REWRITTEN TO ADD THE LOGIC FOR THE CONTACT SWITCH

    switch (*state)
    {
    case 0:
        moveStepper(ZERO_FORWARD_TARGET);
        stepper.setMaxSpeed(MAX_SPEED);
        *state = 1;
        debugln("moving to pickup");
        enableMagnet();
        break;
    case 1:
    debugln("case 1");
        if (digitalRead(inductiveProx) == 1 && digitalRead(carriageContactSwitch) == 0) {
            stepper.stop();
            *state = 2; // weight detected, ready to pick up
            debugln("encountered weight");
        } else if (digitalRead(inductiveProx) == 0 && digitalRead(carriageContactSwitch) == 0) {
            // *state = 10; // dummy weight/obstacle detected
            stepper.stop();
            *state = 2; // for testing
            debugln("encountered weight");
        } else if (digitalRead(lowerLimitSwitch) == 0) {
            stepper.stop();
            *state = 10; // failed
        }
        break;
    case 2:
        moveStepper(DROPOFF_POSITION);
        stepper.setMaxSpeed(MAX_SPEED);
        debugln("moving stepper back");
        *state = 3;
        break;
    case 3:
        debugln("waiting for stepper to reach target");
        if (stepper.currentPosition() <= DROPOFF_POSITION) {
            *state = 4;
            debugln("stepper has reached destination");
        }
        break;
    case 4:
        disableMagnet();
        debugln("dropping weight");
        *state = 5;
        break;
    case 5: // completed
    moveStepper(IDLE_POSITION);
        break;
    
    default:
        break; 
    }
}

bool zero(int* state) {
    // place stepper right next to bottom limit switch or else this will not work
    static bool zeroed = false;
    static bool initial = true;

    if (zeroed == true) {
        zeroed = false;
    }

    if (initial) {
    stepper.setMaxSpeed(MAX_SPEED);
    initial = false;
    }

    switch (*state)
    {
    case 0: 
        // try moving in first direction - N.B. if this initial direction is
        // right then the rest should work fine without requiring rewrite

        moveStepper(ZERO_FORWARD_TARGET);
        *state = 1;
        break;
    case 1: //
        if (digitalRead(lowerLimitSwitch) == 1) {
            debugln("limit switch not detected");
            if (stepper.currentPosition() >= ZERO_FORWARD_TARGET) {
                debugln("trying other direction");
                stepper.moveTo(ZERO_REAR_TARGET);
                *state = 2; // try moving the other way?
            }
        } else {
            // zeroed successfully
            debugln("zeroed successfully");
            stepper.stop();
            stepper.setCurrentPosition(0);
            stepper.setMaxSpeed(MAX_SPEED);
            zeroed = true;
            moveStepper(IDLE_POSITION);
        }
        break;

    case 2:
        if (digitalRead(lowerLimitSwitch) == 1) {
            if (stepper.currentPosition() <= ZERO_REAR_TARGET) {
                debugln("failed to zero");
                *state = 3; // zero has failed
            }
        } else {
            debugln("zeroed successfully on second try");
            // zeroed successfully
            stepper.stop();
            stepper.setCurrentPosition(0);
            stepper.setMaxSpeed(MAX_SPEED);
            zeroed = true;
            moveStepper(IDLE_POSITION);
        }
        break;

    case 3: //stepper has failed

        break;

    default:
        break;
    }
    return zeroed;
}
