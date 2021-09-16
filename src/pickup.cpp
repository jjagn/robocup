// pickup.c - module for controlling weight pickup;
#include <Arduino.h>

#define NUM_PULSES 200
#define RAISE 1
#define LOWER 0
#define TIMEOUT_LIMIT 1000

const int electromagnetPin = 34;
const int stepPin = 2;
const int dirPin = 3;
const int upperLimitSwitch = 0;
const int lowerLimitSwitch = 0;

void initPickup(void) {
    pinMode(electromagnetPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void moveStepper(int duration) {
    for(int i = 0; i < duration; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
    }
}

void moveStepperToLimit(int limitSwitch) {
    // man i hope this doesn't break stuff terribly
    int timer = 0;
    while (digitalRead(limitSwitch) == 0 && timer < TIMEOUT_LIMIT) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
        timer += 1;
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

void pickup(void) {
    // pick up weight
    enableMagnet();
    delay(100);

    digitalWrite(dirPin, RAISE); // set stepper to direction, may need to be swapped

    moveStepper(200);
    // moveStepperToLimit(upperLimitSwitch);

    digitalWrite(dirPin, LOWER); // set stepper to opposite direction

    // drop weight
    disableMagnet();

    moveStepper(200);
    // moveStepperToLimit(lowerLimitSwitch);
}
