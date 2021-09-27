#ifndef SENSOR_STRUCT_H
#define SENSOR_STRUCT_H

#define BUFFER_SIZE 5

#include <Arduino.h>

struct Sensor {
    // creates a sensor struct that holds all the relevant data about a sensor. create by calling Sensor(sensor pin, proximity value)
    int sensorPin;
    int prox = 0;
    int index = 0;
    int value = 0;
    int sum = 0;
    int readings[BUFFER_SIZE];
    int averaged = 0;

    Sensor(int sP, int p) {
        sensorPin = sP;
        pinMode(sP, OUTPUT);
        prox = p;
    }

    void averageSensor(void) {
        sum = sum - readings[index];       // Remove the oldest entry from the sum
        value = analogRead(sensorPin);
        readings[index] = value;           // Add the newest reading to the window
        sum = sum + value;                 // Add the newest reading to the sum
        index = (index+1) % BUFFER_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

        averaged = sum / BUFFER_SIZE;      // Divide the sum of the window by the window size for the result
        Serial.println(averaged);
    }
};

struct SensorGroup {
    static Sensor* right;
    static Sensor* left;
    static int rightVal;
    static int leftVal;
    static int output;
};

struct WeightSensors : public SensorGroup {

        WeightSensors(Sensor* r, Sensor* l) {
        right = r;
        left = l;
    }
        
        int detectWeights() {

            leftVal = left->averaged;
            rightVal = right->averaged;
            
            if (rightVal > right->prox && leftVal > left->prox) {
                // we have detected a weight, somewhere out there
                output = leftVal - rightVal;
            } else {
                output = 32767;
            }
            return output;
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
        // Serial.println("Obstacle right");
        output = 1;

    } else if ((rightVal < right->prox) && (leftVal > left->prox)) {
        // Serial.println("Obstacle left");
        output = 2;

    } else if ((rightVal < right->prox) && (leftVal < left->prox)) {
        // Serial.println("All clear");
        output = 3;

    } else {
        // Serial.println("Fully obstructed");
        output = 4;
    }
    return output;
    }
};

#endif