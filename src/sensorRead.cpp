// sensorRead.cpp reads the given sensor and averages the result, given
// the sensor pin

#include<Arduino.h>

#define FILTER_PERIOD 10

int readSensors(int sensorPin) {
    int sum = 0;
    int i = 0;
    
    while(i < FILTER_PERIOD) {
        int tempVal = analogRead(sensorPin);

        sum += tempVal;
        i++;
    }

    return (sum / FILTER_PERIOD);
}