/*
This sample code is for testing the 4 stepper motors
All motors will rotate the same direction at the same time
*/

#include <Arduino.h>

int dirPin = 31;
int stepPin = 30;

void setup()
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  //Setup step and direction pins for output
  pinMode(dirPin,OUTPUT);
  pinMode(stepPin,OUTPUT);
}

void loop()
{
  int j;
  
  //Set direction for all channels
  digitalWrite(dirPin,HIGH);
  
  for(j=0;j<=1000;j++)            //Move 1000 steps
  {
    digitalWrite(stepPin,LOW);
    delayMicroseconds(100);
    digitalWrite(stepPin,HIGH);
    delay(100);
  }
}
