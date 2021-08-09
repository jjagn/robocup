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
    

void motorControl(int IRVal) {
    switch(IRVal) {
        case(1):
            Serial.println("Obstacle right");
            right.writeMicroseconds(FORWARD_SLOW);      // turn left 
            left.writeMicroseconds(BACKWARD_SLOW);       // 
            break;

        case(2):
            Serial.println("Obstacle left");
            right.writeMicroseconds(BACKWARD_SLOW);      // turn right
            left.writeMicroseconds(FORWARD_SLOW);       // 
            break;

        case(3):
            Serial.println("All clear");
            right.writeMicroseconds(FORWARD_FAST);      // forward slow  
            left.writeMicroseconds(FORWARD_FAST);       // 
            break;

        case(4):
            Serial.println("Fully obstructed");
            // drive both backwards then turn left?
            right.writeMicroseconds(BACKWARD_SLOW);      
            left.writeMicroseconds(BACKWARD_SLOW);
            delay(1000);
            right.writeMicroseconds(BACKWARD_SLOW);
            left.writeMicroseconds(FORWARD_SLOW);   
            delay(500);
            break;
    }
}
