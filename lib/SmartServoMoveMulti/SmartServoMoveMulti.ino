#include "Herkulex.h"

int motorA=0xfd; //motor ID - verify your ID !!!!
int motorB=0x02;
/*
0xfd or 253 is the default
0xfe or 254 is broadcast, ie all motors
*/
 
void setup() 
{
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  Herkulex.beginSerial2(115200);       //open serial port 2 to talk to the motors
  Herkulex.reboot(motorA);             //reboot first motor
  Herkulex.reboot(motorB);             //reboot second motor
  delay(500);
  Herkulex.initialize();               //initialize motors
  delay(200); 
}
 
void loop()
{
  Herkulex.moveOneAngle(motorA, -100, 1000, LED_BLUE); //move motorA backward
  delay(1200);
  Herkulex.moveOneAngle(motorB, 100, 1000, LED_BLUE);  //move motorB forward
  delay(1200);   
  Herkulex.moveOneAngle(motorA, 100, 1000, LED_GREEN); //move motorA backward
  delay(1200);
  Herkulex.moveOneAngle(motorB, -100, 1000, LED_GREEN); //move motor forward
  delay(1200);
}
