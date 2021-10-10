#include <Arduino.h>
#include <Servo.h>
#include "debug.h"
#include "robostruct.h"

#define FORWARD_FAST 2000
#define FORWARD_SLOW 1750
#define STOP 1500
#define BACKWARD_SLOW 1250 
#define BACKWARD_FAST 1000
#define ACCELERATION 50
#define P_GAIN 10
#define I_GAIN 0.2
#define D_GAIN 3
#define TIME_STEP 1

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
    
}

void turnLeft() {
    // debugln("turning left");
    // smartControl(FORWARD_FAST, BACKWARD_FAST);
    right.writeMicroseconds(FORWARD_FAST);      // turn left 
    left.writeMicroseconds(BACKWARD_FAST); 
}

void turnRight() {
    // debugln("turning right");
    // smartControl(BACKWARD_FAST, FORWARD_FAST);
    right.writeMicroseconds(BACKWARD_FAST);      // turn right
    left.writeMicroseconds(FORWARD_FAST); 
}

void driveStraight() {
    // debugln("driving straight");
    // smartControl(FORWARD_FAST, FORWARD_FAST);
    right.writeMicroseconds(FORWARD_FAST);
    left.writeMicroseconds(FORWARD_FAST);
}

void creep() {
    // debugln("creeping forward");
    // smartControl(FORWARD_SLOW, FORWARD_SLOW);
    right.writeMicroseconds(FORWARD_SLOW);
    left.writeMicroseconds(FORWARD_SLOW);
}

void reverse() {
    // debugln("reversing");
    // smartControl(BACKWARD_FAST, BACKWARD_FAST);
    right.writeMicroseconds(BACKWARD_FAST);
    left.writeMicroseconds(BACKWARD_FAST);
}

void stop() {
    right.writeMicroseconds(STOP);
    left.writeMicroseconds(STOP);
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
            delay(2500);
            break;
    }
}