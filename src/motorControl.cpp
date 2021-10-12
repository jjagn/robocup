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
    static unsigned long reverseTimerStart;
    unsigned long currentTime;
    unsigned long timeElapsed;
    static bool reversing = false;
    static bool initial = true;

    static int reverseTime = 750;
    static int turnTime = 1500;

    if (reversing) {
        if (initial) {
            reverseTimerStart = millis();
            initial = false;
            debugln("starting reverse sequence");
        }
        debugln("reversing");
        IRVal = 5;
        currentTime = millis();
    }

    switch(IRVal) {
        case(1):
            turnLeft();
            debugln("turning left");
            break;

        case(2):
        debugln("turning right");
            turnRight();
            break;

        case(3):
            driveStraight();
            debugln("driving straight");
            break;

        case(4):
            reversing = true;
            debugln("reverse mode set");
        case(5):
            currentTime = millis();

            timeElapsed = currentTime - reverseTimerStart;
            if (timeElapsed < reverseTime) {
                debugln("reversing, less than 500ms");
                reverse();
            } else if (timeElapsed < turnTime) {
                debugln("turning left, less than 1000ms");
                turnLeft();
            } else {
                reverseTime += 100;
                turnTime += 100;
                reversing = false;
                debugln("reversing finished");
            }
            break; 
    }
}
