#include <Arduino.h>
#include <Servo.h>
#include "debug.h"
#include "robostruct.h"

#define FORWARD_FAST 2000
#define FORWARD_SLOW 1800
#define STOP 1500
#define BACKWARD_SLOW 1200
#define BACKWARD_FAST 1000
#define ACCELERATION 10

Servo right;      // create servo object to control a servo
Servo left;      // create servo object to control a servo

void initMotors() {
    right.attach(2);  // attaches the servo pin 3 to the servo object
    left.attach(3);  // attaches the servo pin 2 to the servo object

    left.writeMicroseconds(STOP);
    right.writeMicroseconds(STOP);
}

void smartControl(int rightTarget, int leftTarget) {
    // implements motor control with acceleration, hopefully 
    int rightSpeed = right.readMicroseconds();
    int leftSpeed = left.readMicroseconds();
    debug("right speed: "); debugln(rightSpeed);
    debug("left speed: "); debugln(leftSpeed);

    int rightOut = rightSpeed;
    int leftOut = leftSpeed;

    if (rightTarget > rightSpeed) {
        rightOut += ACCELERATION;
        debugln("accelerating right");
    }
    
    if (leftTarget > leftSpeed) {
        leftOut += ACCELERATION;
        debugln("accelerating left");
    }

    if (rightTarget < rightSpeed) {
        rightOut -= ACCELERATION;
        debugln("decelerating right");
    }

    if (leftTarget < leftSpeed) {
        debugln("decelerating left");
        leftOut -= ACCELERATION;
    }

    debug("right output speed: "); debugln(rightOut);
    debug("left output speed: "); debugln(leftOut);

    right.writeMicroseconds(rightOut);
    left.writeMicroseconds(leftOut);
}

void turnLeft() {
    debugln("turning left");
    smartControl(FORWARD_FAST, BACKWARD_FAST);
}

void turnRight() {
    debugln("turning right");
    smartControl(BACKWARD_FAST, FORWARD_FAST); 
}

void driveStraight() {
    debugln("driving straight");
    smartControl(FORWARD_FAST, FORWARD_FAST);
}

void creep() {
    debugln("creeping forward");
    smartControl(FORWARD_SLOW, FORWARD_SLOW);
}

void reverse() {
    debugln("reversing");
    smartControl(BACKWARD_FAST, BACKWARD_FAST);
}

void motorControl(int IRVal) {
    switch(IRVal) {
        case(1):
            turnLeft();
            break;

        case(2):
            turnRight();
            break;

        case(3):
            driveStraight();
            break;

        case(4):
            // debugln("Fully obstructed");
            // drive both backwards then turn left?
            turnLeft(); 
            break;
    }
}