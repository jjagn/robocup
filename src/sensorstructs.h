#ifndef SENSOR_STRUCT_H
#define SENSOR_STRUCT_H

#define BUFFER_SIZE 5

#include <Arduino.h>
#include "debug.h"

// CABLES GO INTO CON 3 AND OUT OF CON 1 IF DAISY CHAINING
// OA21 medium range
// 42SK short range

// this information has once again proven useful

struct Sensor {
    // creates a sensor struct that holds all the relevant data about a sensor. create by calling Sensor(sensor pin, proximity value)
    int sensorPin;
    int prox = 0;
    int index = 0;
    int value = 0;
    int sum = 0;
    int readings[BUFFER_SIZE];
    int averaged = 0;
    String name;

    Sensor(int sP, int p, String n) {
        // constructor for sensor struct, also initialises sensor pin
        sensorPin = sP;
        pinMode(sP, INPUT);
        prox = p;
        name = n;
    }

    void averageSensor(void) {
        sum = sum - readings[index];       // Remove the oldest entry from the sum
        value = analogRead(sensorPin);
        // THESE SERIAL PRINTS TAKE ~7 ms!!
        // debug("Sensor: ");
        // debugln(name);
        // debug("Sensor value:");
        // debug("raw:");
        // debug(value);
        // debug(",");
        readings[index] = value;           // Add the newest reading to the window
        sum = sum + value;                 // Add the newest reading to the sum
        index = (index+1) % BUFFER_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

        averaged = sum / BUFFER_SIZE;      // Divide the sum of the window by the window size for the result
        // debug("filtered:");
        // debugln(averaged);
    }
};

struct SensorGroup {
    Sensor *right;
    Sensor *left;
    Sensor *rightUpper;
    Sensor *leftUpper;
    int rightVal;
    int leftVal;
    int rightUpperVal;
    int leftUpperVal;
    int output;
};

struct WeightSensors : public SensorGroup {
        WeightSensors(Sensor *r, Sensor *l, Sensor *ru, Sensor *lu) {
        right = r;
        left = l;
        rightUpper = ru;
        leftUpper = lu;
    }

    int weightDetectCounter = 0;
    int weightDetectThreshold = 5;
        
        int detectWeights() {

            leftVal = left->averaged;
            rightVal = right->averaged;
            rightUpperVal = rightUpper->averaged;
            leftUpperVal = leftUpper->averaged;
            int result = 100;

            // debug("left upper sensor value: ");
            // debugln(leftUpperVal);

            // debug("right upper sensor value: ");
            // debugln(rightUpperVal);

            if (leftVal > left->prox) {
                debugln("left weight sensor sees something");
                if (leftUpperVal < leftUpper->prox) {
                    debugln("left upper weight sensor all clear");
                    // weight detected left
                    debug("counting up for debouncing: ");
                    debugln(weightDetectCounter);

                    if(weightDetectCounter++ > weightDetectThreshold) {
                        debugln("debounce limit reached");
                        result = 1;
                        // weightDetectCounter = 0;
                    }
                } else {
                    //wall detected left
                    debugln("wall detected left");
                    weightDetectCounter = 0;
                    result = 10;
                }
            } else if (rightVal > right->prox) {
                debugln("right weight sensor sees something");
                if (rightUpperVal < rightUpper->prox) {
                    debugln("right upper weight sensor all clear");
                    // weight detected right
                    debug("counting up for debouncing: ");
                    debugln(weightDetectCounter);

                    if(weightDetectCounter++ > weightDetectThreshold) {
                            debugln("debounce limit reached");
                            result = 2;
                            // weightDetectCounter = 0;
                    } 
                } else {
                    // wall detected right
                    debugln("wall detected right");
                    weightDetectCounter = 0;
                    result = 11;
                }
            } else {
                weightDetectCounter = 0;
            }
            
            
            return result;
        }
    };

struct ObstacleSensors : public SensorGroup {

    ObstacleSensors(Sensor* r, Sensor* l) {
        right = r;
        left = l;
    }

    int detectObstacle() {
    // takes sensor values from both IR sensors, outputs 1, 2, 3, or 4 for
    // obstacles right, left, all clear or fully obstructed respectively

    rightVal = right->averaged;
    leftVal = left->averaged;

    if ((rightVal > right->prox) && (leftVal < left->prox)) {
        debugln("Obstacle right");
        output = 1;

    } else if ((rightVal < right->prox) && (leftVal > left->prox)) {
        debugln("Obstacle left");
        output = 2;

    } else if ((rightVal < right->prox) && (leftVal < left->prox)) {
        // debugln("All clear");
        output = 3;

    } else {
        debugln("Fully obstructed");
        output = 4;
    }
    return output;
    }
};

#endif