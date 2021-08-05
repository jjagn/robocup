#include <Arduino.h>

const int motorA = 33;
const int motorB = 32;

const int IRin1 = A9;
const int IRin2 = A10;
//const int hall = ;

static int IRRightVal;
static int IRVal2;

const int outputMode = 'Serial';

static int in; // input from serial
static bool serialFlag;

void setup() {
    pinMode(49, OUTPUT);                 // Pin 49 is used to enable IO power
    digitalWrite(49, 1);                 // Enable IO power on main CPU board
    Serial.begin(9600);
}

void loop() {
    in = Serial.read();

    if (in == 's') {
        serialFlag = true;
    } else if (in == 'p') {
        serialFlag = false; 
    }

    if (serialFlag) {
        if (outputMode == 'CSV') {
            Serial.print(IRRightVal);
            Serial.print(','); 
        } else {
            Serial.println(IRRightVal);
            delay(100);
        }
    }

    IRRightVal = analogRead(IRin1);
    IRVal2 = analogRead(IRin2);
    
    delay(10); // poll at 100Hz
}