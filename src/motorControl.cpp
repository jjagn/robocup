#include <Arduino.h>
#include <Servo.h>

#define FORWARD_FAST 2000
#define FORWARD_SLOW 1800
#define STOP 1500
#define BACKWARD_SLOW 1200
#define BACKWARD_FAST 1000

Servo right;      // create servo object to control a servo
Servo left;      // create servo object to control a servo


void initMotors() {
    right.attach(2);  // attaches the servo pin 3 to the servo object
    left.attach(3);  // attaches the servo pin 2 to the servo object

    left.writeMicroseconds(STOP);
    right.writeMicroseconds(STOP);
}

void turnLeft() {
    // Serial.println("turning left");
    right.writeMicroseconds(FORWARD_SLOW);      // turn left 
    left.writeMicroseconds(BACKWARD_SLOW); 
}

void turnRight() {
    // Serial.println("turning right");
    right.writeMicroseconds(BACKWARD_SLOW);      // turn right
    left.writeMicroseconds(FORWARD_SLOW);  
}

void driveStraight() {
    // Serial.println("driving straight");
    right.writeMicroseconds(FORWARD_FAST);
    left.writeMicroseconds(FORWARD_FAST);
}

void creep() {
    // Serial.println("creeping forward");
    right.writeMicroseconds(FORWARD_SLOW);
    left.writeMicroseconds(FORWARD_SLOW);
}

void reverse() {
    // Serial.println("reversing");
    right.writeMicroseconds(BACKWARD_SLOW);
    left.writeMicroseconds(BACKWARD_SLOW);
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
            // Serial.println("Fully obstructed");
            // drive both backwards then turn left?
            reverse();
            delay(1000);
            turnLeft();
            delay(500);
            break;
    }
}