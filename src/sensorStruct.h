#ifndef SENSOR_STRUCT_H
#define SENSOR_STRUCT_H

#define BUFFER_SIZE 5

#include <Arduino.h>
struct Sensors {
    struct Sensor {
        int sensorPin;
        int index = 0;
        int value = 0;
        int sum = 0;
        int readings[BUFFER_SIZE];
        int averaged = 0;

        Sensor(int sP) {
            sensorPin = sP;
            pinMode(sP, OUTPUT);
        }

        void averageSensor(void) {
            sum = sum - readings[index];       // Remove the oldest entry from the sum
            value = analogRead(sensorPin);
            readings[index] = value;           // Add the newest reading to the window
            sum = sum + value;                 // Add the newest reading to the sum
            index = (index+1) % BUFFER_SIZE;   // Increment the index, and wrap to 0 if it exceeds the window size

            averaged = sum / BUFFER_SIZE;      // Divide the sum of the window by the window size for the result
        }
    };
};
#endif