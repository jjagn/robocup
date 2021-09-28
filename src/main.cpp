#include <Arduino.h>
#include <Servo.h>

#include <TimerOne.h>

#include "motorControl.h"
#include "robostruct.h"
#include "pickup.h"
#include "sensorstructs.h"

#define WEIGHT_DETECTION_ANGULAR_TOLERANCE 50

#define TIMER_UPDATE_FREQ 1000
#define TIMER_INTERRUPT_PERIOD 1000000 / TIMER_UPDATE_FREQ

#define SCAN_RATE_HZ 10
#define SCAN_PRESCALER TIMER_UPDATE_FREQ / SCAN_RATE_HZ

// g for global = g for good
// declaring the many beautiful structs our program uses
struct Robostruct Robot;
struct Sensor rightObstacle = Sensor(A1, 200);
struct Sensor leftObstacle = Sensor(A0, 200);
struct Sensor rightWeight = Sensor(A3, 100);
struct Sensor leftWeight = Sensor(A2, 100);

struct ObstacleSensors obstacleSensors = ObstacleSensors(&rightObstacle, &leftObstacle);
struct WeightSensors weightSensors = WeightSensors(&rightWeight, &leftWeight);

const int proximityPin = A5;

void TimerHandler() {
    // Serial.println("timer handler triggered");
    if (++Robot.scan > SCAN_PRESCALER) {
        Robot.scanFlag = true;
        Robot.scan = 0;
    }
}

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(115200);

    // Initialise timer ITimer1
    Timer1.initialize(TIMER_INTERRUPT_PERIOD);
    Timer1.attachInterrupt(TimerHandler);

    // initialise motors and pickup mechanism, mainly just setting pins to output and shit
    initMotors();
    initPickup();

    pinMode(proximityPin, INPUT);

    Robot.mode = 3; // DEBUG
}

void loop() {
    // Serial.println("looped");

    // this function updates the current position of the stepper motor, 
    // calculates what it needs to do and where it needs to go
    runStepper();

    if (Robot.scanFlag) {
        // e.g. if timer interrupt has triggered and it's time to scan
        Serial.println("scanflag reset");
        Robot.scanFlag = false;  

        // should read all sensors and update them
        // I SINCERELY HOPE THIS IS FASTER THAN THE SENSOR UPDATE FREQUENCY
        rightObstacle.averageSensor();
        leftObstacle.averageSensor();
        rightWeight.averageSensor();
        leftWeight.averageSensor();

        Robot.weightHeading = weightSensors.detectWeights(); // scan lower sensors to see if there is a weight present
        Robot.IRResult = obstacleSensors.detectObstacle(); // take input from IR reading function
    }

    switch(Robot.mode) {
        case (0): // SEARCHING FOR WEIGHTS
            if (Robot.weightHeading == 32767) { // i.e. whatever output from detectWeights means there are no weights
                Robot.mode = 0;
            } else {
                Robot.mode = 1; // we got one
            }

            motorControl(Robot.IRResult); // control motors based on sensor output

            break;
        
        case(1): // WEIGHT DETECTED, MOVING TO PICKUP
            Robot.weightPresent = digitalRead(proximityPin); // check whether there is a weight in the pickup area

            Robot.weightCollectTimeout++;

            if (Robot.weightCollectTimeout > Robot.weightCollectTimeoutLimit) {
                Robot.resetTimeout();
                Robot.mode = 0;
                // Serial.println("aborting pickup");
            }
            // while weight is not in detection zone/if weight is not in detection zone
            // as long as the weight is not just a wall
            if (!Robot.weightPresent) {
                if (Robot.weightHeading > WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnRight();
                } else if (Robot.weightHeading < -WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnLeft();
                } else {
                    creep();
                }
            } else {
                pickup(); // this function should turn on the magnet, lift it, drop the weight into the bin, and return the magnet to zero
                Robot.mode = 0;
                Robot.collectedWeights++;
            }


                break;
        case(3): //DEBUG MODE
        Serial.println(digitalRead(proximityPin));
        enableMagnet();
    }
}
