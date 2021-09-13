// pickup.c - module for controlling weight pickup;
#include <Arduino.h>

#define NUM_PULSES 200
#define RAISE 1
#define LOWER 0

const int electromagnetPin = 1;
const int stepPin = 2;
const int dirPin = 3;
const int upperLimitSwitch = 0;
const int lowerLimitSwitch = 0;

void initPickup(void) {
    pinMode(electromagnetPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
}

void pickup(void) {
    digitalWrite(electromagnetPin, 1);
    delay(100);
    digitalWrite(dirPin, RAISE); // set stepper to direction, may need to be swapped

    moveStepper(NUM_PULSES);
    // moveStepperToLimit(upperLimitSwitch);
    digitalWrite(dirPin, LOWER); // set stepper to opposite direction

    moveStepper(NUM_PULSES);
    // moveStepperToLimit(lowerLimitSwitch);
    
    
}

void moveStepper(int duration) {
    for(int i = 0; i < NUM_PULSES; i++) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
    }
}

void moveStepperToLimit(int limitSwitch) {
    while (digitalRead(limitSwitch) == 0) {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(500);
    }
}