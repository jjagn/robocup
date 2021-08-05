#include <Servo.h>

Servo myservo;      // create servo object to control a servo

int potpin = A0; // analog pin used to connect the potentiometer
int val;            // variable to read the value from the analog pin

void setup()
{ 
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  myservo.attach(3);  // attaches the servo  to the servo object
}

void loop() 
{ 
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, 500, 2500);  // scale it to use it with the servo (value between 500 and 2500) 
  myservo.writeMicroseconds(val);      // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
} 



