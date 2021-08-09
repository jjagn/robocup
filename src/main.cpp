#include <Arduino.h>
#include <Servo.h>

#include "IRSense.h"
#include "motorControl.h"

int IRResult;

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(9600);

    initMotors();
}

void loop() {

    delay(50); // poll at 1kHz
    IRResult = IRSense(); // take input from IR reading function
    motorControl(IRResult); // control motors based on sensor output
}