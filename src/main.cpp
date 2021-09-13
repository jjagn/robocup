#include <Arduino.h>
#include <Servo.h>

#include "obstacleDetection.h"
#include "motorControl.h"
#include "weightDetection.h"
#include "robostruct.h"
#include "pickup.h"

#define WEIGHT_DETECTION_ANGULAR_TOLERANCE 50
#define KNOCK_O_CLOCK 6000000
#define POLL_RATE 100
#define DELAY 1000 / POLL_RATE

int weightHeading;
int IRResult;
int mode = 0;
bool weightPresent = false;
int weightCollectTimeOut = 0;
unsigned long roundStartTime = 0;

struct Robostruct Robot;

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(9600);

    roundStartTime = millis();

    // read colour sensor and store base colour

    initMotors();
}

void loop() {

    delay(DELAY);

    if ((Robot.collectedWeights > Robot.weightGoal) || ((millis() - roundStartTime) >= KNOCK_O_CLOCK)) {
                    Robot.mode = 2; // RTB
                }

    switch(Robot.mode) {
        case (0): // SEARCHING FOR WEIGHTS
            Serial.println("searching for weights, mode 1");

            weightHeading = detectWeights(); // scan lower sensors to see if there is a weight present
            IRResult = detectObstacle(); // take input from IR reading function
            
            if (weightHeading == 32767) { // i.e. whatever output from detectWeights means there are no weights
                Robot.mode = 0;
            } else {
                // Robot.mode = 1; // we got one
            }

            motorControl(IRResult); // control motors based on sensor output

            break;
        
        case(1): // WEIGHT DETECTED, MOVING TO PICKUP
            Serial.println("weights detected");

            weightHeading = detectWeights(); // scan lower sensors to see if there is a weight present
            //IRResult = detectObstacle(); // take input from IR reading function
            //weightPresent = readProximity(); // check whether there is a weight in the pickup area

            Robot.weightCollectTimeout++;

            if (Robot.weightCollectTimeout > Robot.weightCollectTimeoutLimit) {
                Robot.resetTimeout();
                Robot.mode = 0;
                Serial.println("aborting pickup");
            }
            // while weight is not in detection zone/if weight is not in detection zone
            // as long as the weight is not just a wall
            if (!weightPresent) {
                if (weightHeading > WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnRight();
                } else if (weightHeading < -WEIGHT_DETECTION_ANGULAR_TOLERANCE) {
                    turnLeft();
                } else {
                    creep();
                }
            } else {
                //pickup(); // this function should turn on the magnet, lift it, drop the weight into the bin, and return the magnet to zero
                Robot.mode = 0;
                Robot.collectedWeights++;
            }


                break;

        case(2): // RETURNING TO BASE?
                // have no idea how this will be achieved - do a 180, follow walls
                // until we are over our colour?
                Serial.println("returning to base");
            break;

    // motorControl(angleError, distanceError)


    }
}
