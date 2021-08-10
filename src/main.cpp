#include <Arduino.h>
#include <Servo.h>

#include "obstacleDetection.h"
#include "motorControl.h"
#include "weightDetection.h"

int IRResult;

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(9600);

    initMotors();
}

void loop() {

    delay(250); // poll at 1kHz
    IRResult = detectObstacle(); // take input from IR reading function
    motorControl(IRResult); // control motors based on sensor output
    // Serial.println("looped");
}