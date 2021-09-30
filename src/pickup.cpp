// pickup.c - module for controlling weight pickup;
#include <Arduino.h>
#include <AccelStepper.h>

#define NUM_PULSES 200
#define RAISE 1
#define LOWER 0
#define TIMEOUT_LIMIT 1000
#define STEP_PERIOD 500
#define MAX_SPEED 1000

const int electromagnetPin = 34;
const int stepPin = 42;
const int dirPin = 43;
const int upperLimitSwitch = 0;
const int lowerLimitSwitch = 0;

AccelStepper stepper(AccelStepper::DRIVER, stepPin, dirPin);

void initPickup(void) {
    pinMode(electromagnetPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    stepper.setMaxSpeed(1000);
    stepper.setAcceleration(2000);
}

void moveStepper(int target) {
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
    if (*state == 0) {
        moveStepper(100);
        *state = 1;
    } else if (*state == 1) {
        if (digitalRead(A5) == 1) {
            *state = 2;
        }
    } else if (*state == 2) {
        enableMagnet();
        moveStepper(-2000);
        *state = 3;
    } else if (*state == 3) {
        if (stepper.currentPosition() == -2000) {
            *state = 4;
        }
    } else if (*state == 4) {
        disableMagnet();
    }
}
