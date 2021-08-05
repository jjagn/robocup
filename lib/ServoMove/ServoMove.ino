#include <Servo.h>

Servo myservo;      // create servo object to control a servo

void setup()
{ 
  pinMode(49, OUTPUT);                 //Pin 49 is used to enable IO power
  digitalWrite(49, 1);                 //Enable IO power on main CPU board
  
  myservo.attach(3);  // attaches the servo  to the servo object useing pin 3
}

void loop() 
{ 
  myservo.writeMicroseconds(1000);      // sets the servo position full speed backward
  delay(1500);                           // waits for the servo to get there 
  myservo.writeMicroseconds(2000);      // sets the servo position full speed forward
  delay(1500);                           // waits for the servo to get there 
} 



