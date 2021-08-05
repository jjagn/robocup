#include <Arduino.h>
#include <Servo.h>

#define FORWARD_FAST 2000
#define FORWARD_SLOW 1800
#define STOP 1500
#define BACKWARD_SLOW 1200
#define BACKWARD_FAST 1000

const int IRin1 = A0;
const int IRin2 = A1;

Servo right;      // create servo object to control a servo
Servo left;      // create servo object to control a servo

static int IRRightVal;
static int IRLeftVal;

static int RightProx = 100;
static int LeftProx = 200;

int mode = 0;

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(9600);

    right.attach(2);  // attaches the servo pin 3 to the servo object
    left.attach(3);  // attaches the servo pin 2 to the servo object
}

void loop() {
    IRRightVal = analogRead(IRin1);
    IRLeftVal = analogRead(IRin2);

    delay(50); // poll at 1kHz

    if (mode == 0) {
        if ((IRRightVal > RightProx) && (IRLeftVal < LeftProx)) {
            Serial.println("Obstacle right");
            right.writeMicroseconds(FORWARD_SLOW);      // turn left 
            left.writeMicroseconds(BACKWARD_SLOW);       // 

        } else if ((IRRightVal < RightProx) && (IRLeftVal > LeftProx)) {
            Serial.println("Obstacle left");
            right.writeMicroseconds(BACKWARD_SLOW);      // turn right
            left.writeMicroseconds(FORWARD_SLOW);       // 

        } else if ((IRRightVal < RightProx) && (IRLeftVal < LeftProx)) {
            Serial.println("All clear");
            right.writeMicroseconds(FORWARD_FAST);      // forward slow  
            left.writeMicroseconds(FORWARD_FAST);       // 

        } else {
            Serial.println("Fully obstructed");
            // drive both backwards then turn left?
            right.writeMicroseconds(BACKWARD_SLOW);      
            left.writeMicroseconds(BACKWARD_SLOW);
            delay(1000);
            right.writeMicroseconds(BACKWARD_SLOW);
            left.writeMicroseconds(FORWARD_SLOW);   
            delay(500);  

        }
    // } else if (mode == 1) {
    //     Serial.print("Right: ");
    //     Serial.print(IRRightVal);
    //     Serial.print(" Left: ");
    //     Serial.println(IRLeftVal);
    // }
    }
}